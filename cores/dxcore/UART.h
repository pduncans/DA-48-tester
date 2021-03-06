/*
  UART.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#pragma once

#include <inttypes.h>
#include "api/HardwareSerial.h"
#include "pins_arduino.h"

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
// NOTE: a "power of 2" buffer size is recommended to dramatically
//       optimize all the modulo operations for ring buffers.
// WARNING: When buffer sizes are increased to > 256, the buffer index
// variables are automatically increased in size, but the extra
// atomicity guards needed for that are not implemented. This will
// often work, but occasionally a race condition can occur that makes
// Serial behave erratically. See https://github.com/arduino/Arduino/issues/2405
#if !defined(SERIAL_TX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_TX_BUFFER_SIZE 16
#else
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_RX_BUFFER_SIZE 16
#else
#define SERIAL_RX_BUFFER_SIZE 64
#endif
#endif
#if (SERIAL_TX_BUFFER_SIZE>256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif
#if  (SERIAL_RX_BUFFER_SIZE>256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif

// Define config for Serial.begin(baud, config); Arduino API defines these differently in a way that takes more storage!
// thou shalt not
#undef SERIAL_5N1
#undef SERIAL_6N1
#undef SERIAL_7N1
#undef SERIAL_8N1
#undef SERIAL_5N2
#undef SERIAL_6N2
#undef SERIAL_7N2
#undef SERIAL_8N2
#undef SERIAL_5E1
#undef SERIAL_6E1
#undef SERIAL_7E1
#undef SERIAL_8E1
#undef SERIAL_5E2
#undef SERIAL_6E2
#undef SERIAL_7E2
#undef SERIAL_8E2
#undef SERIAL_5O1
#undef SERIAL_6O1
#undef SERIAL_7O1
#undef SERIAL_8O1
#undef SERIAL_5O2
#undef SERIAL_6O2
#undef SERIAL_7O2
#undef SERIAL_8O2

// Define config for Serial.begin(baud, config); Default: SERIAL_8N1
#define SERIAL_5N1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_5BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc)
#define SERIAL_6N1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_6BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc)
#define SERIAL_7N1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_7BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc)
#define SERIAL_8N1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc)

#define SERIAL_5N2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_5BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_2BIT_gc)
#define SERIAL_6N2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_6BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_2BIT_gc)
#define SERIAL_7N2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_7BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_2BIT_gc)
#define SERIAL_8N2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_2BIT_gc)

#define SERIAL_5E1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_5BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_1BIT_gc)
#define SERIAL_6E1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_6BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_1BIT_gc)
#define SERIAL_7E1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_7BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_1BIT_gc)
#define SERIAL_8E1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_1BIT_gc)

#define SERIAL_5E2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_5BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_2BIT_gc)
#define SERIAL_6E2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_6BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_2BIT_gc)
#define SERIAL_7E2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_7BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_2BIT_gc)
#define SERIAL_8E2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_EVEN_gc | USART_SBMODE_2BIT_gc)

#define SERIAL_5O1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_5BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_1BIT_gc)
#define SERIAL_6O1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_6BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_1BIT_gc)
#define SERIAL_7O1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_7BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_1BIT_gc)
#define SERIAL_8O1 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_1BIT_gc)

#define SERIAL_5O2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_5BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_2BIT_gc)
#define SERIAL_6O2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_6BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_2BIT_gc)
#define SERIAL_7O2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_7BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_2BIT_gc)
#define SERIAL_8O2 (USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_ODD_gc  | USART_SBMODE_2BIT_gc)

#ifndef __AVR_DD__
  #define SERIAL_PIN_SETS 2
#else
  #define SERIAL_PIN_SETS 5 /* oh FFS, this is not what I thought would be painful... WAY more complicated to handle than SPI, which also has like a billion options now. */
#endif
class UartClass : public HardwareSerial
{
  protected:
    volatile USART_t * const _hwserial_module;

    volatile uint8_t _hwserial_dre_interrupt_vect_num;

    struct UartPinSet {
      uint8_t const rx_pin;
      uint8_t const tx_pin;
      uint8_t const mux;
    } _hw_set[SERIAL_PIN_SETS];

    uint8_t _pin_set;

    // Has any byte been written to the UART since begin()
    bool _written;

    volatile rx_buffer_index_t _rx_buffer_head;
    volatile rx_buffer_index_t _rx_buffer_tail;
    volatile tx_buffer_index_t _tx_buffer_head;
    volatile tx_buffer_index_t _tx_buffer_tail;

    // Don't put any members after these buffers, since only the first
    // 32 bytes of this struct can be accessed quickly using the ldd
    // instruction.
    volatile unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
    volatile unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

  public:
    #ifdef __AVR_DD__
      inline UartClass(volatile USART_t *hwserial_module, uint8_t dre_vect_num, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t uart_mux,
        uint8_t hwserial_rx_pin_swap,  uint8_t hwserial_tx_pin_swap,  uint8_t uart_mux_swap,
        uint8_t hwserial_rx_pin_swap2, uint8_t hwserial_tx_pin_swap2, uint8_t uart_mux_swap2,
        uint8_t hwserial_rx_pin_swap3 = NOT_A_PIN, uint8_t hwserial_tx_pin_swap3 = NOT_A_PIN, uint8_t uart_mux_swap3 = NOT_A_PIN,
        uint8_t hwserial_rx_pin_swap4 = NOT_A_PIN, uint8_t hwserial_tx_pin_swap4 = NOT_A_PIN, uint8_t uart_mux_swap4 = NOT_A_PIN);
    #else
      inline UartClass(volatile USART_t *hwserial_module, uint8_t dre_vect_num, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t uart_mux, uint8_t hwserial_rx_pin_swap, uint8_t hwserial_tx_pin_swap, uint8_t uart_mux_swap);
    #endif
    bool pins(uint8_t tx, uint8_t rx);
    bool swap(uint8_t state = 1);
    void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
    void begin(unsigned long, uint16_t);
    void end();
    void printHex(const uint8_t b);
    void printHex(const uint16_t w, bool swaporder=0);
    void printHex(const uint32_t l, bool swaporder=0);
    void printHex(const int8_t b) {printHex((uint8_t)b);}
    void printHex(const char b) {printHex((uint8_t)b);}
    void printHexln(const uint8_t b) {printHex(b);println();}
    void printHexln(const uint16_t w, bool swaporder=0) {printHex(w,swaporder);println();}
    void printHexln(const uint32_t l, bool swaporder=0) {printHex(l,swaporder);println();}
    void printHexln(const int8_t b) {printHex((uint8_t)b);println();}
    void printHexln(const char b) {printHex((uint8_t)b);println();}
    void printHexln(const int16_t w, bool swaporder=0) {printHex((uint16_t)w,swaporder);println();}
    void printHexln(const int32_t l, bool swaporder=0) {printHex((uint16_t)l,swaporder);println();}
    uint8_t * printHex(uint8_t* p,uint8_t len, char sep=0);
    uint16_t * printHex(uint16_t* p, uint8_t len, char sep=0, bool swaporder=0);
    volatile uint8_t * printHex(volatile uint8_t* p,uint8_t len, char sep=0);
    volatile uint16_t * printHex(volatile uint16_t* p, uint8_t len, char sep=0, bool swaporder=0);
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    explicit operator bool() { return true; }

    // Interrupt handlers - Not intended to be called externally
    inline void _rx_complete_irq(void);
    void _tx_data_empty_irq(void);

  private:
    void _poll_tx_data_empty(void);
};

#if defined(HWSERIAL0)
  extern UartClass Serial0;
  #define HAVE_HWSERIAL0
#endif
#if defined(HWSERIAL1)
  extern UartClass Serial1;
  #define HAVE_HWSERIAL1
#endif
#if defined(HWSERIAL2)
  extern UartClass Serial2;
  #define HAVE_HWSERIAL2
#endif
#if defined(HWSERIAL3)
  extern UartClass Serial3;
  #define HAVE_HWSERIAL3
#endif
#if defined(HWSERIAL4)
  extern UartClass Serial4;
  #define HAVE_HWSERIAL4
#endif
#if defined(HWSERIAL5)
  extern UartClass Serial5;
  #define HAVE_HWSERIAL5
#endif

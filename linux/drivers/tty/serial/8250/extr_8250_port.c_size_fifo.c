#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 unsigned char UART_FCR_CLEAR_RCVR ; 
 unsigned char UART_FCR_CLEAR_XMIT ; 
 unsigned char UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_CONF_MODE_A ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_MCR_LOOP ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned char serial8250_in_MCR (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_out_MCR (struct uart_8250_port*,unsigned char) ; 
 unsigned short serial_dl_read (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_dl_write (struct uart_8250_port*,unsigned short) ; 
 unsigned char serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int size_fifo(struct uart_8250_port *up)
{
	unsigned char old_fcr, old_mcr, old_lcr;
	unsigned short old_dl;
	int count;

	old_lcr = serial_in(up, UART_LCR);
	serial_out(up, UART_LCR, 0);
	old_fcr = serial_in(up, UART_FCR);
	old_mcr = serial8250_in_MCR(up);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
		    UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	serial8250_out_MCR(up, UART_MCR_LOOP);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	old_dl = serial_dl_read(up);
	serial_dl_write(up, 0x0001);
	serial_out(up, UART_LCR, 0x03);
	for (count = 0; count < 256; count++)
		serial_out(up, UART_TX, count);
	mdelay(20);/* FIXME - schedule_timeout */
	for (count = 0; (serial_in(up, UART_LSR) & UART_LSR_DR) &&
	     (count < 256); count++)
		serial_in(up, UART_RX);
	serial_out(up, UART_FCR, old_fcr);
	serial8250_out_MCR(up, old_mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_dl_write(up, old_dl);
	serial_out(up, UART_LCR, old_lcr);

	return count;
}
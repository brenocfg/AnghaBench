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
struct uart_port {int dummy; } ;
struct uart_8250_port {int capabilities; int lcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_DLAB ; 
 int UART_NATSEMI ; 
 int /*<<< orphan*/  UART_OMAP_OSC_12M_SEL ; 
 scalar_t__ is_omap1510_8250 (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_dl_write (struct uart_8250_port*,unsigned int) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

void serial8250_do_set_divisor(struct uart_port *port, unsigned int baud,
			       unsigned int quot, unsigned int quot_frac)
{
	struct uart_8250_port *up = up_to_u8250p(port);

	/* Workaround to enable 115200 baud on OMAP1510 internal ports */
	if (is_omap1510_8250(up)) {
		if (baud == 115200) {
			quot = 1;
			serial_port_out(port, UART_OMAP_OSC_12M_SEL, 1);
		} else
			serial_port_out(port, UART_OMAP_OSC_12M_SEL, 0);
	}

	/*
	 * For NatSemi, switch to bank 2 not bank 1, to avoid resetting EXCR2,
	 * otherwise just set DLAB
	 */
	if (up->capabilities & UART_NATSEMI)
		serial_port_out(port, UART_LCR, 0xe0);
	else
		serial_port_out(port, UART_LCR, up->lcr | UART_LCR_DLAB);

	serial_dl_write(up, quot);
}
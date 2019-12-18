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

/* Variables and functions */
 int /*<<< orphan*/  serial8250_do_set_divisor (struct uart_port*,unsigned int,unsigned int,unsigned int) ; 
 int serial_port_in (struct uart_port*,int) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void xr17v35x_set_divisor(struct uart_port *p, unsigned int baud,
				 unsigned int quot, unsigned int quot_frac)
{
	serial8250_do_set_divisor(p, baud, quot, quot_frac);

	/* Preserve bits not related to baudrate; DLD[7:4]. */
	quot_frac |= serial_port_in(p, 0x2) & 0xf0;
	serial_port_out(p, 0x2, quot_frac);
}
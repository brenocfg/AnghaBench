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
struct uart_port {int flags; unsigned int custom_divisor; int /*<<< orphan*/  uartclk; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int UPF_SPD_CUST ; 
 int UPF_SPD_MASK ; 

unsigned int
uart_get_divisor(struct uart_port *port, unsigned int baud)
{
	unsigned int quot;

	/*
	 * Old custom speed handling.
	 */
	if (baud == 38400 && (port->flags & UPF_SPD_MASK) == UPF_SPD_CUST)
		quot = port->custom_divisor;
	else
		quot = DIV_ROUND_CLOSEST(port->uartclk, 16 * baud);

	return quot;
}
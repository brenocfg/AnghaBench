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
struct uart_8250_port {scalar_t__ gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_MCR ; 
 int /*<<< orphan*/  mctrl_gpio_set (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_MCR_to_TIOCM (int) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void serial8250_out_MCR(struct uart_8250_port *up, int value)
{
	serial_out(up, UART_MCR, value);

	if (up->gpios)
		mctrl_gpio_set(up->gpios, serial8250_MCR_to_TIOCM(value));
}
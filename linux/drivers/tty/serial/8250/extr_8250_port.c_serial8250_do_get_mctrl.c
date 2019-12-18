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
struct uart_8250_port {scalar_t__ gpios; } ;

/* Variables and functions */
 unsigned int mctrl_gpio_get (scalar_t__,unsigned int*) ; 
 unsigned int serial8250_MSR_to_TIOCM (unsigned int) ; 
 unsigned int serial8250_modem_status (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

unsigned int serial8250_do_get_mctrl(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned int status;
	unsigned int val;

	serial8250_rpm_get(up);
	status = serial8250_modem_status(up);
	serial8250_rpm_put(up);

	val = serial8250_MSR_to_TIOCM(status);
	if (up->gpios)
		return mctrl_gpio_get(up->gpios, &val);

	return val;
}
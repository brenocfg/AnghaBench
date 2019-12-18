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
struct uart_8250_port {int bugs; int /*<<< orphan*/  ier; int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int UART_BUG_NOMSR ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_MSI ; 
 int /*<<< orphan*/  mctrl_gpio_enable_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void serial8250_enable_ms(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);

	/* no MSR capabilities */
	if (up->bugs & UART_BUG_NOMSR)
		return;

	mctrl_gpio_enable_ms(up->gpios);

	up->ier |= UART_IER_MSI;

	serial8250_rpm_get(up);
	serial_port_out(port, UART_IER, up->ier);
	serial8250_rpm_put(up);
}
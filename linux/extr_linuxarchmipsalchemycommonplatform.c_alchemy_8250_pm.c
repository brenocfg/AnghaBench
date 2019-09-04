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

__attribute__((used)) static void alchemy_8250_pm(struct uart_port *port, unsigned int state,
			    unsigned int old_state)
{
#ifdef CONFIG_SERIAL_8250
	switch (state) {
	case 0:
		alchemy_uart_enable(CPHYSADDR(port->membase));
		serial8250_do_pm(port, state, old_state);
		break;
	case 3:		/* power off */
		serial8250_do_pm(port, state, old_state);
		alchemy_uart_disable(CPHYSADDR(port->membase));
		break;
	default:
		serial8250_do_pm(port, state, old_state);
		break;
	}
#endif
}
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
 int /*<<< orphan*/  serial_txx9_initialize (struct uart_port*) ; 

__attribute__((used)) static void
serial_txx9_pm(struct uart_port *port, unsigned int state,
	      unsigned int oldstate)
{
	/*
	 * If oldstate was -1 this is called from
	 * uart_configure_port().  In this case do not initialize the
	 * port now, because the port was already initialized (for
	 * non-console port) or should not be initialized here (for
	 * console port).  If we initialized the port here we lose
	 * serial console settings.
	 */
	if (state == 0 && oldstate != -1)
		serial_txx9_initialize(port);
}
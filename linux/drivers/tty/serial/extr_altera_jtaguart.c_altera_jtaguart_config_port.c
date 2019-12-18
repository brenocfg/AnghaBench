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
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ ALTERA_JTAGUART_CONTROL_REG ; 
 int /*<<< orphan*/  PORT_ALTERA_JTAGUART ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void altera_jtaguart_config_port(struct uart_port *port, int flags)
{
	port->type = PORT_ALTERA_JTAGUART;

	/* Clear mask, so no surprise interrupts. */
	writel(0, port->membase + ALTERA_JTAGUART_CONTROL_REG);
}
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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct ltq_uart_port {int /*<<< orphan*/  common_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lqasc_irq ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static int request_irq_intel(struct uart_port *port)
{
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	int retval;

	retval = request_irq(ltq_port->common_irq, lqasc_irq, 0,
			     "asc_irq", port);
	if (retval)
		dev_err(port->dev, "failed to request asc_irq\n");

	return retval;
}
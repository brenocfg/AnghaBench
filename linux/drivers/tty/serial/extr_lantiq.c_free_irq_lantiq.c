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
struct ltq_uart_port {int /*<<< orphan*/  err_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static void free_irq_lantiq(struct uart_port *port)
{
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	free_irq(ltq_port->tx_irq, port);
	free_irq(ltq_port->rx_irq, port);
	free_irq(ltq_port->err_irq, port);
}
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
struct ltq_uart_port {int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  err_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  lqasc_err_int ; 
 int /*<<< orphan*/  lqasc_rx_int ; 
 int /*<<< orphan*/  lqasc_tx_int ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static int request_irq_lantiq(struct uart_port *port)
{
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	int retval;

	retval = request_irq(ltq_port->tx_irq, lqasc_tx_int,
			     0, "asc_tx", port);
	if (retval) {
		dev_err(port->dev, "failed to request asc_tx\n");
		return retval;
	}

	retval = request_irq(ltq_port->rx_irq, lqasc_rx_int,
			     0, "asc_rx", port);
	if (retval) {
		dev_err(port->dev, "failed to request asc_rx\n");
		goto err1;
	}

	retval = request_irq(ltq_port->err_irq, lqasc_err_int,
			     0, "asc_err", port);
	if (retval) {
		dev_err(port->dev, "failed to request asc_err\n");
		goto err2;
	}
	return 0;

err2:
	free_irq(ltq_port->rx_irq, port);
err1:
	free_irq(ltq_port->tx_irq, port);
	return retval;
}
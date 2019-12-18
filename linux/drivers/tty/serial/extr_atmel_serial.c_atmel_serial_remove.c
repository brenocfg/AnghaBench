#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  line; } ;
struct TYPE_4__ {int /*<<< orphan*/ * of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct atmel_uart_port {int /*<<< orphan*/ * clk; TYPE_1__ rx_ring; int /*<<< orphan*/  tasklet_tx; int /*<<< orphan*/  tasklet_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_ports_in_use ; 
 int /*<<< orphan*/  atmel_uart ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 int uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int atmel_serial_remove(struct platform_device *pdev)
{
	struct uart_port *port = platform_get_drvdata(pdev);
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	int ret = 0;

	tasklet_kill(&atmel_port->tasklet_rx);
	tasklet_kill(&atmel_port->tasklet_tx);

	device_init_wakeup(&pdev->dev, 0);

	ret = uart_remove_one_port(&atmel_uart, port);

	kfree(atmel_port->rx_ring.buf);

	/* "port" is allocated statically, so we shouldn't free it */

	clear_bit(port->line, atmel_ports_in_use);

	clk_put(atmel_port->clk);
	atmel_port->clk = NULL;
	pdev->dev.of_node = NULL;

	return ret;
}
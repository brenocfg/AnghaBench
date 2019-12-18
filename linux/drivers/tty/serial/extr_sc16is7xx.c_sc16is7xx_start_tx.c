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
struct sc16is7xx_port {int /*<<< orphan*/  kworker; } ;
struct sc16is7xx_one {int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sc16is7xx_one* to_sc16is7xx_one (struct uart_port*,struct uart_port*) ; 

__attribute__((used)) static void sc16is7xx_start_tx(struct uart_port *port)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	struct sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	kthread_queue_work(&s->kworker, &one->tx_work);
}
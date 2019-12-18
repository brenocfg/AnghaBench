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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct clps711x_port {scalar_t__ tx_enabled; } ;

/* Variables and functions */
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uart_clps711x_stop_tx(struct uart_port *port)
{
	struct clps711x_port *s = dev_get_drvdata(port->dev);

	if (s->tx_enabled) {
		disable_irq(port->irq);
		s->tx_enabled = 0;
	}
}
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
struct serio {struct rpckbd_data* port_data; } ;
struct rpckbd_data {int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct serio*) ; 

__attribute__((used)) static void rpckbd_close(struct serio *port)
{
	struct rpckbd_data *rpckbd = port->port_data;

	free_irq(rpckbd->rx_irq, port);
	free_irq(rpckbd->tx_irq, port);
}
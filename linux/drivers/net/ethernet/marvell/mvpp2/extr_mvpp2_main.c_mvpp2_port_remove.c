#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_port {int ntxqs; int /*<<< orphan*/  dev; scalar_t__ link_irq; TYPE_1__** txqs; int /*<<< orphan*/  stats; int /*<<< orphan*/  pcpu; scalar_t__ phylink; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_queue_vectors_deinit (struct mvpp2_port*) ; 
 int /*<<< orphan*/  phylink_destroy (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_port_remove(struct mvpp2_port *port)
{
	int i;

	unregister_netdev(port->dev);
	if (port->phylink)
		phylink_destroy(port->phylink);
	free_percpu(port->pcpu);
	free_percpu(port->stats);
	for (i = 0; i < port->ntxqs; i++)
		free_percpu(port->txqs[i]->pcpu);
	mvpp2_queue_vectors_deinit(port);
	if (port->link_irq)
		irq_dispose_mapping(port->link_irq);
	free_netdev(port->dev);
}
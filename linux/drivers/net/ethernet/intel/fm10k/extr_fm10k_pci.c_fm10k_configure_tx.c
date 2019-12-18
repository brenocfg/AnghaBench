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
struct fm10k_intfc {int num_tx_queues; int /*<<< orphan*/ * tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_configure_tx_ring (struct fm10k_intfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_enable_tx_ring (struct fm10k_intfc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_configure_tx(struct fm10k_intfc *interface)
{
	int i;

	/* Setup the HW Tx Head and Tail descriptor pointers */
	for (i = 0; i < interface->num_tx_queues; i++)
		fm10k_configure_tx_ring(interface, interface->tx_ring[i]);

	/* poll here to verify that Tx rings are now enabled */
	for (i = 0; i < interface->num_tx_queues; i++)
		fm10k_enable_tx_ring(interface, interface->tx_ring[i]);
}
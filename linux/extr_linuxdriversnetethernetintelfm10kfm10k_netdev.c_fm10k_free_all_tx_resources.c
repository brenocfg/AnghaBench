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
 int /*<<< orphan*/  fm10k_free_tx_resources (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_free_all_tx_resources(struct fm10k_intfc *interface)
{
	int i = interface->num_tx_queues;

	while (i--)
		fm10k_free_tx_resources(interface->tx_ring[i]);
}
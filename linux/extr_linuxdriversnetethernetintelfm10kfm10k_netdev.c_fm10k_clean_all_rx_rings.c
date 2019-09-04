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
struct fm10k_intfc {int num_rx_queues; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_clean_rx_ring (int /*<<< orphan*/ ) ; 

void fm10k_clean_all_rx_rings(struct fm10k_intfc *interface)
{
	int i;

	for (i = 0; i < interface->num_rx_queues; i++)
		fm10k_clean_rx_ring(interface->rx_ring[i]);
}
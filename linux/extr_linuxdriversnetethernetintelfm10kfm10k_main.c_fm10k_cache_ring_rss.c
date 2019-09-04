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
struct fm10k_intfc {int num_rx_queues; int num_tx_queues; TYPE_2__** tx_ring; TYPE_1__** rx_ring; } ;
struct TYPE_4__ {int reg_idx; } ;
struct TYPE_3__ {int reg_idx; } ;

/* Variables and functions */

__attribute__((used)) static void fm10k_cache_ring_rss(struct fm10k_intfc *interface)
{
	int i;

	for (i = 0; i < interface->num_rx_queues; i++)
		interface->rx_ring[i]->reg_idx = i;

	for (i = 0; i < interface->num_tx_queues; i++)
		interface->tx_ring[i]->reg_idx = i;
}
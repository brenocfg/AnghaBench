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
struct igb_adapter {int num_tx_queues; scalar_t__* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_free_tx_resources (scalar_t__) ; 

__attribute__((used)) static void igb_free_all_tx_resources(struct igb_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++)
		if (adapter->tx_ring[i])
			igb_free_tx_resources(adapter->tx_ring[i]);
}
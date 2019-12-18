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
struct igb_adapter {int num_tx_queues; TYPE_1__** tx_ring; } ;
struct TYPE_2__ {scalar_t__ launchtime_enable; } ;

/* Variables and functions */

__attribute__((used)) static bool is_any_txtime_enabled(struct igb_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		if (adapter->tx_ring[i]->launchtime_enable)
			return true;
	}

	return false;
}
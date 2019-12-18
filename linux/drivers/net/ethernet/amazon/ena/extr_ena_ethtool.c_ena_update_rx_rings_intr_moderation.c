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
struct ena_adapter {int num_queues; TYPE_1__* rx_ring; int /*<<< orphan*/  ena_dev; } ;
struct TYPE_2__ {unsigned int smoothed_interval; } ;

/* Variables and functions */
 unsigned int ena_com_get_nonadaptive_moderation_interval_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_update_rx_rings_intr_moderation(struct ena_adapter *adapter)
{
	unsigned int val;
	int i;

	val = ena_com_get_nonadaptive_moderation_interval_rx(adapter->ena_dev);

	for (i = 0; i < adapter->num_queues; i++)
		adapter->rx_ring[i].smoothed_interval = val;
}
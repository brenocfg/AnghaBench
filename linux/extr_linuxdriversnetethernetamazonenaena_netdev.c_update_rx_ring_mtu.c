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
struct ena_adapter {int num_queues; TYPE_1__* rx_ring; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */

__attribute__((used)) static void update_rx_ring_mtu(struct ena_adapter *adapter, int mtu)
{
	int i;

	for (i = 0; i < adapter->num_queues; i++)
		adapter->rx_ring[i].mtu = mtu;
}
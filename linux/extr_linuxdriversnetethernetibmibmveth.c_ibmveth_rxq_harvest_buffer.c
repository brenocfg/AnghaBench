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
struct TYPE_4__ {size_t index; size_t num_slots; int toggle; TYPE_1__* queue_addr; } ;
struct ibmveth_adapter {TYPE_2__ rx_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  correlator; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibmveth_remove_buffer_from_pool (struct ibmveth_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmveth_rxq_harvest_buffer(struct ibmveth_adapter *adapter)
{
	ibmveth_remove_buffer_from_pool(adapter, adapter->rx_queue.queue_addr[adapter->rx_queue.index].correlator);

	if (++adapter->rx_queue.index == adapter->rx_queue.num_slots) {
		adapter->rx_queue.index = 0;
		adapter->rx_queue.toggle = !adapter->rx_queue.toggle;
	}
}
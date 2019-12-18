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
struct ena_adapter {int num_queues; TYPE_2__* rx_ring; TYPE_1__* tx_ring; } ;
struct TYPE_4__ {int ring_size; } ;
struct TYPE_3__ {int ring_size; } ;

/* Variables and functions */

__attribute__((used)) static void set_io_rings_size(struct ena_adapter *adapter,
				     int new_tx_size, int new_rx_size)
{
	int i;

	for (i = 0; i < adapter->num_queues; i++) {
		adapter->tx_ring[i].ring_size = new_tx_size;
		adapter->rx_ring[i].ring_size = new_rx_size;
	}
}
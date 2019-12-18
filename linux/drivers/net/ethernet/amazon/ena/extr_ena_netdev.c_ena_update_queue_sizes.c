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
typedef  void* u32 ;
struct ena_adapter {void* requested_rx_ring_size; void* requested_tx_ring_size; int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 int /*<<< orphan*/  ena_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_init_io_rings (struct ena_adapter*) ; 
 int ena_up (struct ena_adapter*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ena_update_queue_sizes(struct ena_adapter *adapter,
			   u32 new_tx_size,
			   u32 new_rx_size)
{
	bool dev_up;

	dev_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);
	ena_close(adapter->netdev);
	adapter->requested_tx_ring_size = new_tx_size;
	adapter->requested_rx_ring_size = new_rx_size;
	ena_init_io_rings(adapter);
	return dev_up ? ena_up(adapter) : 0;
}
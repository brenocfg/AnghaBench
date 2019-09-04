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
typedef  scalar_t__ u32 ;
struct igbvf_adapter {int requested_itr; TYPE_2__* rx_ring; int /*<<< orphan*/  total_rx_bytes; int /*<<< orphan*/  total_rx_packets; TYPE_1__* tx_ring; int /*<<< orphan*/  total_tx_bytes; int /*<<< orphan*/  total_tx_packets; } ;
struct TYPE_4__ {scalar_t__ itr_range; scalar_t__ itr_val; int set_itr; } ;
struct TYPE_3__ {scalar_t__ itr_range; scalar_t__ itr_val; int set_itr; } ;

/* Variables and functions */
 scalar_t__ igbvf_range_to_itr (scalar_t__) ; 
 void* igbvf_update_itr (struct igbvf_adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* low_latency ; 
 scalar_t__ lowest_latency ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void igbvf_set_itr(struct igbvf_adapter *adapter)
{
	u32 new_itr;

	adapter->tx_ring->itr_range =
			igbvf_update_itr(adapter,
					 adapter->tx_ring->itr_val,
					 adapter->total_tx_packets,
					 adapter->total_tx_bytes);

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (adapter->requested_itr == 3 &&
	    adapter->tx_ring->itr_range == lowest_latency)
		adapter->tx_ring->itr_range = low_latency;

	new_itr = igbvf_range_to_itr(adapter->tx_ring->itr_range);

	if (new_itr != adapter->tx_ring->itr_val) {
		u32 current_itr = adapter->tx_ring->itr_val;
		/* this attempts to bias the interrupt rate towards Bulk
		 * by adding intermediate steps when interrupt rate is
		 * increasing
		 */
		new_itr = new_itr > current_itr ?
			  min(current_itr + (new_itr >> 2), new_itr) :
			  new_itr;
		adapter->tx_ring->itr_val = new_itr;

		adapter->tx_ring->set_itr = 1;
	}

	adapter->rx_ring->itr_range =
			igbvf_update_itr(adapter, adapter->rx_ring->itr_val,
					 adapter->total_rx_packets,
					 adapter->total_rx_bytes);
	if (adapter->requested_itr == 3 &&
	    adapter->rx_ring->itr_range == lowest_latency)
		adapter->rx_ring->itr_range = low_latency;

	new_itr = igbvf_range_to_itr(adapter->rx_ring->itr_range);

	if (new_itr != adapter->rx_ring->itr_val) {
		u32 current_itr = adapter->rx_ring->itr_val;

		new_itr = new_itr > current_itr ?
			  min(current_itr + (new_itr >> 2), new_itr) :
			  new_itr;
		adapter->rx_ring->itr_val = new_itr;

		adapter->rx_ring->set_itr = 1;
	}
}
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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_adapter {int itr; scalar_t__ link_speed; int flags2; scalar_t__ tx_itr; int itr_setting; scalar_t__ rx_itr; TYPE_1__* rx_ring; scalar_t__ msix_entries; int /*<<< orphan*/  total_rx_bytes; int /*<<< orphan*/  total_rx_packets; int /*<<< orphan*/  total_tx_bytes; int /*<<< orphan*/  total_tx_packets; } ;
struct TYPE_2__ {int itr_val; int set_itr; } ;

/* Variables and functions */
 int FLAG2_DISABLE_AIM ; 
 scalar_t__ SPEED_1000 ; 
#define  bulk_latency 130 
 void* e1000_update_itr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_write_itr (struct e1000_adapter*,int) ; 
#define  low_latency 129 
#define  lowest_latency 128 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void e1000_set_itr(struct e1000_adapter *adapter)
{
	u16 current_itr;
	u32 new_itr = adapter->itr;

	/* for non-gigabit speeds, just fix the interrupt rate at 4000 */
	if (adapter->link_speed != SPEED_1000) {
		current_itr = 0;
		new_itr = 4000;
		goto set_itr_now;
	}

	if (adapter->flags2 & FLAG2_DISABLE_AIM) {
		new_itr = 0;
		goto set_itr_now;
	}

	adapter->tx_itr = e1000_update_itr(adapter->tx_itr,
					   adapter->total_tx_packets,
					   adapter->total_tx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (adapter->itr_setting == 3 && adapter->tx_itr == lowest_latency)
		adapter->tx_itr = low_latency;

	adapter->rx_itr = e1000_update_itr(adapter->rx_itr,
					   adapter->total_rx_packets,
					   adapter->total_rx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (adapter->itr_setting == 3 && adapter->rx_itr == lowest_latency)
		adapter->rx_itr = low_latency;

	current_itr = max(adapter->rx_itr, adapter->tx_itr);

	/* counts and packets in update_itr are dependent on these numbers */
	switch (current_itr) {
	case lowest_latency:
		new_itr = 70000;
		break;
	case low_latency:
		new_itr = 20000;	/* aka hwitr = ~200 */
		break;
	case bulk_latency:
		new_itr = 4000;
		break;
	default:
		break;
	}

set_itr_now:
	if (new_itr != adapter->itr) {
		/* this attempts to bias the interrupt rate towards Bulk
		 * by adding intermediate steps when interrupt rate is
		 * increasing
		 */
		new_itr = new_itr > adapter->itr ?
		    min(adapter->itr + (new_itr >> 2), new_itr) : new_itr;
		adapter->itr = new_itr;
		adapter->rx_ring->itr_val = new_itr;
		if (adapter->msix_entries)
			adapter->rx_ring->set_itr = 1;
		else
			e1000e_write_itr(adapter, new_itr);
	}
}
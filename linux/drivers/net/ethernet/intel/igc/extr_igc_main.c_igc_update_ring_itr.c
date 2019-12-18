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
struct TYPE_4__ {unsigned int total_packets; unsigned int total_bytes; } ;
struct TYPE_3__ {unsigned int total_packets; unsigned int total_bytes; scalar_t__ ring; } ;
struct igc_q_vector {int itr_val; int set_itr; TYPE_2__ tx; TYPE_1__ rx; struct igc_adapter* adapter; } ;
struct igc_adapter {int link_speed; int rx_itr_setting; int tx_itr_setting; } ;

/* Variables and functions */
 int IGC_20K_ITR ; 
 int IGC_4K_ITR ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 int max_t (int /*<<< orphan*/ ,int,unsigned int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void igc_update_ring_itr(struct igc_q_vector *q_vector)
{
	struct igc_adapter *adapter = q_vector->adapter;
	int new_val = q_vector->itr_val;
	int avg_wire_size = 0;
	unsigned int packets;

	/* For non-gigabit speeds, just fix the interrupt rate at 4000
	 * ints/sec - ITR timer value of 120 ticks.
	 */
	switch (adapter->link_speed) {
	case SPEED_10:
	case SPEED_100:
		new_val = IGC_4K_ITR;
		goto set_itr_val;
	default:
		break;
	}

	packets = q_vector->rx.total_packets;
	if (packets)
		avg_wire_size = q_vector->rx.total_bytes / packets;

	packets = q_vector->tx.total_packets;
	if (packets)
		avg_wire_size = max_t(u32, avg_wire_size,
				      q_vector->tx.total_bytes / packets);

	/* if avg_wire_size isn't set no work was done */
	if (!avg_wire_size)
		goto clear_counts;

	/* Add 24 bytes to size to account for CRC, preamble, and gap */
	avg_wire_size += 24;

	/* Don't starve jumbo frames */
	avg_wire_size = min(avg_wire_size, 3000);

	/* Give a little boost to mid-size frames */
	if (avg_wire_size > 300 && avg_wire_size < 1200)
		new_val = avg_wire_size / 3;
	else
		new_val = avg_wire_size / 2;

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	if (new_val < IGC_20K_ITR &&
	    ((q_vector->rx.ring && adapter->rx_itr_setting == 3) ||
	    (!q_vector->rx.ring && adapter->tx_itr_setting == 3)))
		new_val = IGC_20K_ITR;

set_itr_val:
	if (new_val != q_vector->itr_val) {
		q_vector->itr_val = new_val;
		q_vector->set_itr = 1;
	}
clear_counts:
	q_vector->rx.total_bytes = 0;
	q_vector->rx.total_packets = 0;
	q_vector->tx.total_bytes = 0;
	q_vector->tx.total_packets = 0;
}
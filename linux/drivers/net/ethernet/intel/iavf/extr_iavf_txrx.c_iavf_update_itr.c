#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iavf_ring_container {unsigned long next_update; unsigned int target_itr; unsigned int total_packets; unsigned int total_bytes; TYPE_1__* ring; } ;
struct TYPE_6__ {unsigned int target_itr; int /*<<< orphan*/  current_itr; } ;
struct TYPE_5__ {unsigned int target_itr; int /*<<< orphan*/  current_itr; } ;
struct iavf_q_vector {TYPE_3__ rx; TYPE_2__ tx; scalar_t__ itr_countdown; } ;
struct TYPE_4__ {int /*<<< orphan*/  itr_setting; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int IAVF_ITR_ADAPTIVE_BULK ; 
 unsigned int IAVF_ITR_ADAPTIVE_LATENCY ; 
 unsigned int IAVF_ITR_ADAPTIVE_MAX_USECS ; 
 unsigned int IAVF_ITR_ADAPTIVE_MIN_INC ; 
 unsigned int IAVF_ITR_ADAPTIVE_MIN_USECS ; 
 unsigned int IAVF_ITR_MASK ; 
 int /*<<< orphan*/  ITR_IS_DYNAMIC (int /*<<< orphan*/ ) ; 
 scalar_t__ iavf_container_is_rx (struct iavf_q_vector*,struct iavf_ring_container*) ; 
 int /*<<< orphan*/  iavf_itr_divisor (struct iavf_q_vector*) ; 
 unsigned long jiffies ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void iavf_update_itr(struct iavf_q_vector *q_vector,
			    struct iavf_ring_container *rc)
{
	unsigned int avg_wire_size, packets, bytes, itr;
	unsigned long next_update = jiffies;

	/* If we don't have any rings just leave ourselves set for maximum
	 * possible latency so we take ourselves out of the equation.
	 */
	if (!rc->ring || !ITR_IS_DYNAMIC(rc->ring->itr_setting))
		return;

	/* For Rx we want to push the delay up and default to low latency.
	 * for Tx we want to pull the delay down and default to high latency.
	 */
	itr = iavf_container_is_rx(q_vector, rc) ?
	      IAVF_ITR_ADAPTIVE_MIN_USECS | IAVF_ITR_ADAPTIVE_LATENCY :
	      IAVF_ITR_ADAPTIVE_MAX_USECS | IAVF_ITR_ADAPTIVE_LATENCY;

	/* If we didn't update within up to 1 - 2 jiffies we can assume
	 * that either packets are coming in so slow there hasn't been
	 * any work, or that there is so much work that NAPI is dealing
	 * with interrupt moderation and we don't need to do anything.
	 */
	if (time_after(next_update, rc->next_update))
		goto clear_counts;

	/* If itr_countdown is set it means we programmed an ITR within
	 * the last 4 interrupt cycles. This has a side effect of us
	 * potentially firing an early interrupt. In order to work around
	 * this we need to throw out any data received for a few
	 * interrupts following the update.
	 */
	if (q_vector->itr_countdown) {
		itr = rc->target_itr;
		goto clear_counts;
	}

	packets = rc->total_packets;
	bytes = rc->total_bytes;

	if (iavf_container_is_rx(q_vector, rc)) {
		/* If Rx there are 1 to 4 packets and bytes are less than
		 * 9000 assume insufficient data to use bulk rate limiting
		 * approach unless Tx is already in bulk rate limiting. We
		 * are likely latency driven.
		 */
		if (packets && packets < 4 && bytes < 9000 &&
		    (q_vector->tx.target_itr & IAVF_ITR_ADAPTIVE_LATENCY)) {
			itr = IAVF_ITR_ADAPTIVE_LATENCY;
			goto adjust_by_size;
		}
	} else if (packets < 4) {
		/* If we have Tx and Rx ITR maxed and Tx ITR is running in
		 * bulk mode and we are receiving 4 or fewer packets just
		 * reset the ITR_ADAPTIVE_LATENCY bit for latency mode so
		 * that the Rx can relax.
		 */
		if (rc->target_itr == IAVF_ITR_ADAPTIVE_MAX_USECS &&
		    (q_vector->rx.target_itr & IAVF_ITR_MASK) ==
		     IAVF_ITR_ADAPTIVE_MAX_USECS)
			goto clear_counts;
	} else if (packets > 32) {
		/* If we have processed over 32 packets in a single interrupt
		 * for Tx assume we need to switch over to "bulk" mode.
		 */
		rc->target_itr &= ~IAVF_ITR_ADAPTIVE_LATENCY;
	}

	/* We have no packets to actually measure against. This means
	 * either one of the other queues on this vector is active or
	 * we are a Tx queue doing TSO with too high of an interrupt rate.
	 *
	 * Between 4 and 56 we can assume that our current interrupt delay
	 * is only slightly too low. As such we should increase it by a small
	 * fixed amount.
	 */
	if (packets < 56) {
		itr = rc->target_itr + IAVF_ITR_ADAPTIVE_MIN_INC;
		if ((itr & IAVF_ITR_MASK) > IAVF_ITR_ADAPTIVE_MAX_USECS) {
			itr &= IAVF_ITR_ADAPTIVE_LATENCY;
			itr += IAVF_ITR_ADAPTIVE_MAX_USECS;
		}
		goto clear_counts;
	}

	if (packets <= 256) {
		itr = min(q_vector->tx.current_itr, q_vector->rx.current_itr);
		itr &= IAVF_ITR_MASK;

		/* Between 56 and 112 is our "goldilocks" zone where we are
		 * working out "just right". Just report that our current
		 * ITR is good for us.
		 */
		if (packets <= 112)
			goto clear_counts;

		/* If packet count is 128 or greater we are likely looking
		 * at a slight overrun of the delay we want. Try halving
		 * our delay to see if that will cut the number of packets
		 * in half per interrupt.
		 */
		itr /= 2;
		itr &= IAVF_ITR_MASK;
		if (itr < IAVF_ITR_ADAPTIVE_MIN_USECS)
			itr = IAVF_ITR_ADAPTIVE_MIN_USECS;

		goto clear_counts;
	}

	/* The paths below assume we are dealing with a bulk ITR since
	 * number of packets is greater than 256. We are just going to have
	 * to compute a value and try to bring the count under control,
	 * though for smaller packet sizes there isn't much we can do as
	 * NAPI polling will likely be kicking in sooner rather than later.
	 */
	itr = IAVF_ITR_ADAPTIVE_BULK;

adjust_by_size:
	/* If packet counts are 256 or greater we can assume we have a gross
	 * overestimation of what the rate should be. Instead of trying to fine
	 * tune it just use the formula below to try and dial in an exact value
	 * give the current packet size of the frame.
	 */
	avg_wire_size = bytes / packets;

	/* The following is a crude approximation of:
	 *  wmem_default / (size + overhead) = desired_pkts_per_int
	 *  rate / bits_per_byte / (size + ethernet overhead) = pkt_rate
	 *  (desired_pkt_rate / pkt_rate) * usecs_per_sec = ITR value
	 *
	 * Assuming wmem_default is 212992 and overhead is 640 bytes per
	 * packet, (256 skb, 64 headroom, 320 shared info), we can reduce the
	 * formula down to
	 *
	 *  (170 * (size + 24)) / (size + 640) = ITR
	 *
	 * We first do some math on the packet size and then finally bitshift
	 * by 8 after rounding up. We also have to account for PCIe link speed
	 * difference as ITR scales based on this.
	 */
	if (avg_wire_size <= 60) {
		/* Start at 250k ints/sec */
		avg_wire_size = 4096;
	} else if (avg_wire_size <= 380) {
		/* 250K ints/sec to 60K ints/sec */
		avg_wire_size *= 40;
		avg_wire_size += 1696;
	} else if (avg_wire_size <= 1084) {
		/* 60K ints/sec to 36K ints/sec */
		avg_wire_size *= 15;
		avg_wire_size += 11452;
	} else if (avg_wire_size <= 1980) {
		/* 36K ints/sec to 30K ints/sec */
		avg_wire_size *= 5;
		avg_wire_size += 22420;
	} else {
		/* plateau at a limit of 30K ints/sec */
		avg_wire_size = 32256;
	}

	/* If we are in low latency mode halve our delay which doubles the
	 * rate to somewhere between 100K to 16K ints/sec
	 */
	if (itr & IAVF_ITR_ADAPTIVE_LATENCY)
		avg_wire_size /= 2;

	/* Resultant value is 256 times larger than it needs to be. This
	 * gives us room to adjust the value as needed to either increase
	 * or decrease the value based on link speeds of 10G, 2.5G, 1G, etc.
	 *
	 * Use addition as we have already recorded the new latency flag
	 * for the ITR value.
	 */
	itr += DIV_ROUND_UP(avg_wire_size, iavf_itr_divisor(q_vector)) *
	       IAVF_ITR_ADAPTIVE_MIN_INC;

	if ((itr & IAVF_ITR_MASK) > IAVF_ITR_ADAPTIVE_MAX_USECS) {
		itr &= IAVF_ITR_ADAPTIVE_LATENCY;
		itr += IAVF_ITR_ADAPTIVE_MAX_USECS;
	}

clear_counts:
	/* write back value */
	rc->target_itr = itr;

	/* next update should occur within next jiffy */
	rc->next_update = next_update + 1;

	rc->total_bytes = 0;
	rc->total_packets = 0;
}
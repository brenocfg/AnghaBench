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
struct ice_ring_container {unsigned int target_itr; unsigned long next_update; unsigned int total_pkts; unsigned int total_bytes; int /*<<< orphan*/  current_itr; int /*<<< orphan*/  itr_setting; int /*<<< orphan*/  ring; } ;
struct TYPE_3__ {unsigned int target_itr; int /*<<< orphan*/  current_itr; } ;
struct ice_q_vector {TYPE_2__* vsi; struct ice_ring_container rx; TYPE_1__ tx; scalar_t__ itr_countdown; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_info; } ;

/* Variables and functions */
 unsigned int ICE_ITR_ADAPTIVE_BULK ; 
 unsigned int ICE_ITR_ADAPTIVE_LATENCY ; 
 unsigned int ICE_ITR_ADAPTIVE_MAX_USECS ; 
 unsigned int ICE_ITR_ADAPTIVE_MIN_INC ; 
 unsigned int ICE_ITR_ADAPTIVE_MIN_USECS ; 
 unsigned int ICE_ITR_MASK ; 
 int /*<<< orphan*/  ITR_IS_DYNAMIC (int /*<<< orphan*/ ) ; 
 unsigned int ice_adjust_itr_by_size_and_speed (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned long jiffies ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void
ice_update_itr(struct ice_q_vector *q_vector, struct ice_ring_container *rc)
{
	unsigned long next_update = jiffies;
	unsigned int packets, bytes, itr;
	bool container_is_rx;

	if (!rc->ring || !ITR_IS_DYNAMIC(rc->itr_setting))
		return;

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

	container_is_rx = (&q_vector->rx == rc);
	/* For Rx we want to push the delay up and default to low latency.
	 * for Tx we want to pull the delay down and default to high latency.
	 */
	itr = container_is_rx ?
		ICE_ITR_ADAPTIVE_MIN_USECS | ICE_ITR_ADAPTIVE_LATENCY :
		ICE_ITR_ADAPTIVE_MAX_USECS | ICE_ITR_ADAPTIVE_LATENCY;

	/* If we didn't update within up to 1 - 2 jiffies we can assume
	 * that either packets are coming in so slow there hasn't been
	 * any work, or that there is so much work that NAPI is dealing
	 * with interrupt moderation and we don't need to do anything.
	 */
	if (time_after(next_update, rc->next_update))
		goto clear_counts;

	prefetch(q_vector->vsi->port_info);

	packets = rc->total_pkts;
	bytes = rc->total_bytes;

	if (container_is_rx) {
		/* If Rx there are 1 to 4 packets and bytes are less than
		 * 9000 assume insufficient data to use bulk rate limiting
		 * approach unless Tx is already in bulk rate limiting. We
		 * are likely latency driven.
		 */
		if (packets && packets < 4 && bytes < 9000 &&
		    (q_vector->tx.target_itr & ICE_ITR_ADAPTIVE_LATENCY)) {
			itr = ICE_ITR_ADAPTIVE_LATENCY;
			goto adjust_by_size_and_speed;
		}
	} else if (packets < 4) {
		/* If we have Tx and Rx ITR maxed and Tx ITR is running in
		 * bulk mode and we are receiving 4 or fewer packets just
		 * reset the ITR_ADAPTIVE_LATENCY bit for latency mode so
		 * that the Rx can relax.
		 */
		if (rc->target_itr == ICE_ITR_ADAPTIVE_MAX_USECS &&
		    (q_vector->rx.target_itr & ICE_ITR_MASK) ==
		    ICE_ITR_ADAPTIVE_MAX_USECS)
			goto clear_counts;
	} else if (packets > 32) {
		/* If we have processed over 32 packets in a single interrupt
		 * for Tx assume we need to switch over to "bulk" mode.
		 */
		rc->target_itr &= ~ICE_ITR_ADAPTIVE_LATENCY;
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
		itr = rc->target_itr + ICE_ITR_ADAPTIVE_MIN_INC;
		if ((itr & ICE_ITR_MASK) > ICE_ITR_ADAPTIVE_MAX_USECS) {
			itr &= ICE_ITR_ADAPTIVE_LATENCY;
			itr += ICE_ITR_ADAPTIVE_MAX_USECS;
		}
		goto clear_counts;
	}

	if (packets <= 256) {
		itr = min(q_vector->tx.current_itr, q_vector->rx.current_itr);
		itr &= ICE_ITR_MASK;

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
		itr >>= 1;
		itr &= ICE_ITR_MASK;
		if (itr < ICE_ITR_ADAPTIVE_MIN_USECS)
			itr = ICE_ITR_ADAPTIVE_MIN_USECS;

		goto clear_counts;
	}

	/* The paths below assume we are dealing with a bulk ITR since
	 * number of packets is greater than 256. We are just going to have
	 * to compute a value and try to bring the count under control,
	 * though for smaller packet sizes there isn't much we can do as
	 * NAPI polling will likely be kicking in sooner rather than later.
	 */
	itr = ICE_ITR_ADAPTIVE_BULK;

adjust_by_size_and_speed:

	/* based on checks above packets cannot be 0 so division is safe */
	itr = ice_adjust_itr_by_size_and_speed(q_vector->vsi->port_info,
					       bytes / packets, itr);

clear_counts:
	/* write back value */
	rc->target_itr = itr;

	/* next update should occur within next jiffy */
	rc->next_update = next_update + 1;

	rc->total_bytes = 0;
	rc->total_pkts = 0;
}
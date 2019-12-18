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
struct ixgbe_ring_container {unsigned long next_update; unsigned int total_packets; unsigned int itr; unsigned int total_bytes; int /*<<< orphan*/  ring; } ;
struct ixgbe_q_vector {int itr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int link_speed; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int,int) ; 
 unsigned int IXGBE_ITR_ADAPTIVE_BULK ; 
 unsigned int IXGBE_ITR_ADAPTIVE_LATENCY ; 
 unsigned int IXGBE_ITR_ADAPTIVE_MAX_USECS ; 
 int IXGBE_ITR_ADAPTIVE_MIN_INC ; 
 unsigned int IXGBE_ITR_ADAPTIVE_MIN_USECS ; 
#define  IXGBE_LINK_SPEED_100_FULL 132 
#define  IXGBE_LINK_SPEED_10GB_FULL 131 
#define  IXGBE_LINK_SPEED_10_FULL 130 
#define  IXGBE_LINK_SPEED_1GB_FULL 129 
#define  IXGBE_LINK_SPEED_2_5GB_FULL 128 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void ixgbe_update_itr(struct ixgbe_q_vector *q_vector,
			     struct ixgbe_ring_container *ring_container)
{
	unsigned int itr = IXGBE_ITR_ADAPTIVE_MIN_USECS |
			   IXGBE_ITR_ADAPTIVE_LATENCY;
	unsigned int avg_wire_size, packets, bytes;
	unsigned long next_update = jiffies;

	/* If we don't have any rings just leave ourselves set for maximum
	 * possible latency so we take ourselves out of the equation.
	 */
	if (!ring_container->ring)
		return;

	/* If we didn't update within up to 1 - 2 jiffies we can assume
	 * that either packets are coming in so slow there hasn't been
	 * any work, or that there is so much work that NAPI is dealing
	 * with interrupt moderation and we don't need to do anything.
	 */
	if (time_after(next_update, ring_container->next_update))
		goto clear_counts;

	packets = ring_container->total_packets;

	/* We have no packets to actually measure against. This means
	 * either one of the other queues on this vector is active or
	 * we are a Tx queue doing TSO with too high of an interrupt rate.
	 *
	 * When this occurs just tick up our delay by the minimum value
	 * and hope that this extra delay will prevent us from being called
	 * without any work on our queue.
	 */
	if (!packets) {
		itr = (q_vector->itr >> 2) + IXGBE_ITR_ADAPTIVE_MIN_INC;
		if (itr > IXGBE_ITR_ADAPTIVE_MAX_USECS)
			itr = IXGBE_ITR_ADAPTIVE_MAX_USECS;
		itr += ring_container->itr & IXGBE_ITR_ADAPTIVE_LATENCY;
		goto clear_counts;
	}

	bytes = ring_container->total_bytes;

	/* If packets are less than 4 or bytes are less than 9000 assume
	 * insufficient data to use bulk rate limiting approach. We are
	 * likely latency driven.
	 */
	if (packets < 4 && bytes < 9000) {
		itr = IXGBE_ITR_ADAPTIVE_LATENCY;
		goto adjust_by_size;
	}

	/* Between 4 and 48 we can assume that our current interrupt delay
	 * is only slightly too low. As such we should increase it by a small
	 * fixed amount.
	 */
	if (packets < 48) {
		itr = (q_vector->itr >> 2) + IXGBE_ITR_ADAPTIVE_MIN_INC;
		if (itr > IXGBE_ITR_ADAPTIVE_MAX_USECS)
			itr = IXGBE_ITR_ADAPTIVE_MAX_USECS;
		goto clear_counts;
	}

	/* Between 48 and 96 is our "goldilocks" zone where we are working
	 * out "just right". Just report that our current ITR is good for us.
	 */
	if (packets < 96) {
		itr = q_vector->itr >> 2;
		goto clear_counts;
	}

	/* If packet count is 96 or greater we are likely looking at a slight
	 * overrun of the delay we want. Try halving our delay to see if that
	 * will cut the number of packets in half per interrupt.
	 */
	if (packets < 256) {
		itr = q_vector->itr >> 3;
		if (itr < IXGBE_ITR_ADAPTIVE_MIN_USECS)
			itr = IXGBE_ITR_ADAPTIVE_MIN_USECS;
		goto clear_counts;
	}

	/* The paths below assume we are dealing with a bulk ITR since number
	 * of packets is 256 or greater. We are just going to have to compute
	 * a value and try to bring the count under control, though for smaller
	 * packet sizes there isn't much we can do as NAPI polling will likely
	 * be kicking in sooner rather than later.
	 */
	itr = IXGBE_ITR_ADAPTIVE_BULK;

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
		/* Start at 50k ints/sec */
		avg_wire_size = 5120;
	} else if (avg_wire_size <= 316) {
		/* 50K ints/sec to 16K ints/sec */
		avg_wire_size *= 40;
		avg_wire_size += 2720;
	} else if (avg_wire_size <= 1084) {
		/* 16K ints/sec to 9.2K ints/sec */
		avg_wire_size *= 15;
		avg_wire_size += 11452;
	} else if (avg_wire_size < 1968) {
		/* 9.2K ints/sec to 8K ints/sec */
		avg_wire_size *= 5;
		avg_wire_size += 22420;
	} else {
		/* plateau at a limit of 8K ints/sec */
		avg_wire_size = 32256;
	}

	/* If we are in low latency mode half our delay which doubles the rate
	 * to somewhere between 100K to 16K ints/sec
	 */
	if (itr & IXGBE_ITR_ADAPTIVE_LATENCY)
		avg_wire_size >>= 1;

	/* Resultant value is 256 times larger than it needs to be. This
	 * gives us room to adjust the value as needed to either increase
	 * or decrease the value based on link speeds of 10G, 2.5G, 1G, etc.
	 *
	 * Use addition as we have already recorded the new latency flag
	 * for the ITR value.
	 */
	switch (q_vector->adapter->link_speed) {
	case IXGBE_LINK_SPEED_10GB_FULL:
	case IXGBE_LINK_SPEED_100_FULL:
	default:
		itr += DIV_ROUND_UP(avg_wire_size,
				    IXGBE_ITR_ADAPTIVE_MIN_INC * 256) *
		       IXGBE_ITR_ADAPTIVE_MIN_INC;
		break;
	case IXGBE_LINK_SPEED_2_5GB_FULL:
	case IXGBE_LINK_SPEED_1GB_FULL:
	case IXGBE_LINK_SPEED_10_FULL:
		if (avg_wire_size > 8064)
			avg_wire_size = 8064;
		itr += DIV_ROUND_UP(avg_wire_size,
				    IXGBE_ITR_ADAPTIVE_MIN_INC * 64) *
		       IXGBE_ITR_ADAPTIVE_MIN_INC;
		break;
	}

clear_counts:
	/* write back value */
	ring_container->itr = itr;

	/* next update should occur within next jiffy */
	ring_container->next_update = next_update + 1;

	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;
}
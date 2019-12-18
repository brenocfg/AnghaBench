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
typedef  int u8 ;
struct igb_ring_container {unsigned int total_packets; unsigned int total_bytes; int itr; } ;
struct igb_q_vector {int dummy; } ;

/* Variables and functions */
#define  bulk_latency 130 
#define  low_latency 129 
#define  lowest_latency 128 

__attribute__((used)) static void igb_update_itr(struct igb_q_vector *q_vector,
			   struct igb_ring_container *ring_container)
{
	unsigned int packets = ring_container->total_packets;
	unsigned int bytes = ring_container->total_bytes;
	u8 itrval = ring_container->itr;

	/* no packets, exit with status unchanged */
	if (packets == 0)
		return;

	switch (itrval) {
	case lowest_latency:
		/* handle TSO and jumbo frames */
		if (bytes/packets > 8000)
			itrval = bulk_latency;
		else if ((packets < 5) && (bytes > 512))
			itrval = low_latency;
		break;
	case low_latency:  /* 50 usec aka 20000 ints/s */
		if (bytes > 10000) {
			/* this if handles the TSO accounting */
			if (bytes/packets > 8000)
				itrval = bulk_latency;
			else if ((packets < 10) || ((bytes/packets) > 1200))
				itrval = bulk_latency;
			else if ((packets > 35))
				itrval = lowest_latency;
		} else if (bytes/packets > 2000) {
			itrval = bulk_latency;
		} else if (packets <= 2 && bytes < 512) {
			itrval = lowest_latency;
		}
		break;
	case bulk_latency: /* 250 usec aka 4000 ints/s */
		if (bytes > 25000) {
			if (packets > 35)
				itrval = low_latency;
		} else if (bytes < 1500) {
			itrval = low_latency;
		}
		break;
	}

	/* clear work counters since we have the values we need */
	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;

	/* write updated itr to ring container */
	ring_container->itr = itrval;
}
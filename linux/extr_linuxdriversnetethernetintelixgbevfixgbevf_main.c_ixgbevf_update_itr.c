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
typedef  int u64 ;
typedef  int u32 ;
struct ixgbevf_ring_container {int total_bytes; int total_packets; int itr; } ;
struct ixgbevf_q_vector {int itr; } ;

/* Variables and functions */
#define  bulk_latency 130 
#define  low_latency 129 
#define  lowest_latency 128 

__attribute__((used)) static void ixgbevf_update_itr(struct ixgbevf_q_vector *q_vector,
			       struct ixgbevf_ring_container *ring_container)
{
	int bytes = ring_container->total_bytes;
	int packets = ring_container->total_packets;
	u32 timepassed_us;
	u64 bytes_perint;
	u8 itr_setting = ring_container->itr;

	if (packets == 0)
		return;

	/* simple throttle rate management
	 *    0-20MB/s lowest (100000 ints/s)
	 *   20-100MB/s low   (20000 ints/s)
	 *  100-1249MB/s bulk (12000 ints/s)
	 */
	/* what was last interrupt timeslice? */
	timepassed_us = q_vector->itr >> 2;
	bytes_perint = bytes / timepassed_us; /* bytes/usec */

	switch (itr_setting) {
	case lowest_latency:
		if (bytes_perint > 10)
			itr_setting = low_latency;
		break;
	case low_latency:
		if (bytes_perint > 20)
			itr_setting = bulk_latency;
		else if (bytes_perint <= 10)
			itr_setting = lowest_latency;
		break;
	case bulk_latency:
		if (bytes_perint <= 20)
			itr_setting = low_latency;
		break;
	}

	/* clear work counters since we have the values we need */
	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;

	/* write updated itr to ring container */
	ring_container->itr = itr_setting;
}
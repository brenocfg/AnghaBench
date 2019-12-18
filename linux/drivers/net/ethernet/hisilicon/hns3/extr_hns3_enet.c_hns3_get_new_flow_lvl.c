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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int flow_level; } ;
struct hns3_enet_ring_group {int total_packets; int total_bytes; TYPE_2__ coal; TYPE_1__* ring; } ;
struct hns3_enet_tqp_vector {struct hns3_enet_ring_group rx_group; scalar_t__ last_jiffies; } ;
typedef  enum hns3_flow_level_range { ____Placeholder_hns3_flow_level_range } hns3_flow_level_range ;
struct TYPE_3__ {struct hns3_enet_tqp_vector* tqp_vector; } ;

/* Variables and functions */
#define  HNS3_FLOW_HIGH 131 
#define  HNS3_FLOW_LOW 130 
#define  HNS3_FLOW_MID 129 
#define  HNS3_FLOW_ULTRA 128 
 int HNS3_RX_LOW_BYTE_RATE ; 
 int HNS3_RX_MID_BYTE_RATE ; 
 int HNS3_RX_ULTRA_PACKET_RATE ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 

__attribute__((used)) static bool hns3_get_new_flow_lvl(struct hns3_enet_ring_group *ring_group)
{
#define HNS3_RX_LOW_BYTE_RATE 10000
#define HNS3_RX_MID_BYTE_RATE 20000
#define HNS3_RX_ULTRA_PACKET_RATE 40

	enum hns3_flow_level_range new_flow_level;
	struct hns3_enet_tqp_vector *tqp_vector;
	int packets_per_msecs, bytes_per_msecs;
	u32 time_passed_ms;

	tqp_vector = ring_group->ring->tqp_vector;
	time_passed_ms =
		jiffies_to_msecs(jiffies - tqp_vector->last_jiffies);
	if (!time_passed_ms)
		return false;

	do_div(ring_group->total_packets, time_passed_ms);
	packets_per_msecs = ring_group->total_packets;

	do_div(ring_group->total_bytes, time_passed_ms);
	bytes_per_msecs = ring_group->total_bytes;

	new_flow_level = ring_group->coal.flow_level;

	/* Simple throttlerate management
	 * 0-10MB/s   lower     (50000 ints/s)
	 * 10-20MB/s   middle    (20000 ints/s)
	 * 20-1249MB/s high      (18000 ints/s)
	 * > 40000pps  ultra     (8000 ints/s)
	 */
	switch (new_flow_level) {
	case HNS3_FLOW_LOW:
		if (bytes_per_msecs > HNS3_RX_LOW_BYTE_RATE)
			new_flow_level = HNS3_FLOW_MID;
		break;
	case HNS3_FLOW_MID:
		if (bytes_per_msecs > HNS3_RX_MID_BYTE_RATE)
			new_flow_level = HNS3_FLOW_HIGH;
		else if (bytes_per_msecs <= HNS3_RX_LOW_BYTE_RATE)
			new_flow_level = HNS3_FLOW_LOW;
		break;
	case HNS3_FLOW_HIGH:
	case HNS3_FLOW_ULTRA:
	default:
		if (bytes_per_msecs <= HNS3_RX_MID_BYTE_RATE)
			new_flow_level = HNS3_FLOW_MID;
		break;
	}

	if (packets_per_msecs > HNS3_RX_ULTRA_PACKET_RATE &&
	    &tqp_vector->rx_group == ring_group)
		new_flow_level = HNS3_FLOW_ULTRA;

	ring_group->total_bytes = 0;
	ring_group->total_packets = 0;
	ring_group->coal.flow_level = new_flow_level;

	return true;
}
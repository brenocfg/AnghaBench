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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct gb_operation_msg_hdr {int dummy; } ;
struct gb_loopback_transfer_response {int dummy; } ;
struct gb_loopback_transfer_request {int dummy; } ;
struct gb_loopback {int type; int size; int requests_completed; int /*<<< orphan*/  throughput; } ;

/* Variables and functions */
#define  GB_LOOPBACK_TYPE_PING 130 
#define  GB_LOOPBACK_TYPE_SINK 129 
#define  GB_LOOPBACK_TYPE_TRANSFER 128 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  gb_loopback_update_stats_window (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_loopback_throughput_update(struct gb_loopback *gb, u32 latency)
{
	u64 aggregate_size = sizeof(struct gb_operation_msg_hdr) * 2;

	switch (gb->type) {
	case GB_LOOPBACK_TYPE_PING:
		break;
	case GB_LOOPBACK_TYPE_SINK:
		aggregate_size += sizeof(struct gb_loopback_transfer_request) +
				  gb->size;
		break;
	case GB_LOOPBACK_TYPE_TRANSFER:
		aggregate_size += sizeof(struct gb_loopback_transfer_request) +
				  sizeof(struct gb_loopback_transfer_response) +
				  gb->size * 2;
		break;
	default:
		return;
	}

	aggregate_size *= gb->requests_completed;
	aggregate_size *= USEC_PER_SEC;
	gb_loopback_update_stats_window(&gb->throughput, aggregate_size,
					latency);
}
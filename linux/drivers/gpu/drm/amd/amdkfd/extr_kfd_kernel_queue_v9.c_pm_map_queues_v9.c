#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int type; int sdma_engine_id; scalar_t__ write_ptr; int /*<<< orphan*/  doorbell_off; } ;
struct queue {TYPE_4__ properties; int /*<<< orphan*/  gart_mqd_addr; scalar_t__ gws; } ;
struct TYPE_7__ {int /*<<< orphan*/  doorbell_offset; } ;
struct TYPE_6__ {int num_queues; int engine_sel; int gws_control_queue; int /*<<< orphan*/  extended_engine_sel; int /*<<< orphan*/  queue_type; int /*<<< orphan*/  queue_sel; } ;
struct TYPE_5__ {int /*<<< orphan*/  u32All; } ;
struct pm4_mes_map_queues {void* wptr_addr_hi; void* wptr_addr_lo; void* mqd_addr_hi; void* mqd_addr_lo; TYPE_3__ bitfields3; TYPE_2__ bitfields2; TYPE_1__ header; } ;
struct packet_manager {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IT_MAP_QUEUES ; 
#define  KFD_QUEUE_TYPE_COMPUTE 131 
#define  KFD_QUEUE_TYPE_DIQ 130 
#define  KFD_QUEUE_TYPE_SDMA 129 
#define  KFD_QUEUE_TYPE_SDMA_XGMI 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int engine_sel__mes_map_queues__compute_vi ; 
 int engine_sel__mes_map_queues__sdma0_vi ; 
 int /*<<< orphan*/  extended_engine_sel__mes_map_queues__legacy_engine_sel ; 
 int /*<<< orphan*/  extended_engine_sel__mes_map_queues__sdma0_to_7_sel ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_build_pm4_header (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_sel__mes_map_queues__map_to_hws_determined_queue_slots_vi ; 
 int /*<<< orphan*/  queue_type__mes_map_queues__debug_interface_queue_vi ; 
 int /*<<< orphan*/  queue_type__mes_map_queues__normal_compute_vi ; 
 int /*<<< orphan*/  queue_type__mes_map_queues__normal_latency_static_queue_vi ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm_map_queues_v9(struct packet_manager *pm, uint32_t *buffer,
		struct queue *q, bool is_static)
{
	struct pm4_mes_map_queues *packet;
	bool use_static = is_static;

	packet = (struct pm4_mes_map_queues *)buffer;
	memset(buffer, 0, sizeof(struct pm4_mes_map_queues));

	packet->header.u32All = pm_build_pm4_header(IT_MAP_QUEUES,
					sizeof(struct pm4_mes_map_queues));
	packet->bitfields2.num_queues = 1;
	packet->bitfields2.queue_sel =
		queue_sel__mes_map_queues__map_to_hws_determined_queue_slots_vi;

	packet->bitfields2.engine_sel =
		engine_sel__mes_map_queues__compute_vi;
	packet->bitfields2.gws_control_queue = q->gws ? 1 : 0;
	packet->bitfields2.extended_engine_sel =
		extended_engine_sel__mes_map_queues__legacy_engine_sel;
	packet->bitfields2.queue_type =
		queue_type__mes_map_queues__normal_compute_vi;

	switch (q->properties.type) {
	case KFD_QUEUE_TYPE_COMPUTE:
		if (use_static)
			packet->bitfields2.queue_type =
		queue_type__mes_map_queues__normal_latency_static_queue_vi;
		break;
	case KFD_QUEUE_TYPE_DIQ:
		packet->bitfields2.queue_type =
			queue_type__mes_map_queues__debug_interface_queue_vi;
		break;
	case KFD_QUEUE_TYPE_SDMA:
	case KFD_QUEUE_TYPE_SDMA_XGMI:
		use_static = false; /* no static queues under SDMA */
		if (q->properties.sdma_engine_id < 2)
			packet->bitfields2.engine_sel = q->properties.sdma_engine_id +
				engine_sel__mes_map_queues__sdma0_vi;
		else {
			packet->bitfields2.extended_engine_sel =
				extended_engine_sel__mes_map_queues__sdma0_to_7_sel;
			packet->bitfields2.engine_sel = q->properties.sdma_engine_id;
		}
		break;
	default:
		WARN(1, "queue type %d", q->properties.type);
		return -EINVAL;
	}
	packet->bitfields3.doorbell_offset =
			q->properties.doorbell_off;

	packet->mqd_addr_lo =
			lower_32_bits(q->gart_mqd_addr);

	packet->mqd_addr_hi =
			upper_32_bits(q->gart_mqd_addr);

	packet->wptr_addr_lo =
			lower_32_bits((uint64_t)q->properties.write_ptr);

	packet->wptr_addr_hi =
			upper_32_bits((uint64_t)q->properties.write_ptr);

	return 0;
}
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
typedef  void* uint32_t ;
struct TYPE_8__ {unsigned int engine_sel; int num_queues; int /*<<< orphan*/  queue_sel; int /*<<< orphan*/  action; void* extended_engine_sel; } ;
struct TYPE_7__ {void* pasid; } ;
struct TYPE_6__ {void* doorbell_offset0; } ;
struct TYPE_5__ {int /*<<< orphan*/  u32All; } ;
struct pm4_mes_unmap_queues {TYPE_4__ bitfields2; TYPE_3__ bitfields3a; TYPE_2__ bitfields3b; TYPE_1__ header; } ;
struct packet_manager {int dummy; } ;
typedef  enum kfd_unmap_queues_filter { ____Placeholder_kfd_unmap_queues_filter } kfd_unmap_queues_filter ;
typedef  enum kfd_queue_type { ____Placeholder_kfd_queue_type } kfd_queue_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IT_UNMAP_QUEUES ; 
#define  KFD_QUEUE_TYPE_COMPUTE 135 
#define  KFD_QUEUE_TYPE_DIQ 134 
#define  KFD_QUEUE_TYPE_SDMA 133 
#define  KFD_QUEUE_TYPE_SDMA_XGMI 132 
#define  KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES 131 
#define  KFD_UNMAP_QUEUES_FILTER_BY_PASID 130 
#define  KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES 129 
#define  KFD_UNMAP_QUEUES_FILTER_SINGLE_QUEUE 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  action__mes_unmap_queues__preempt_queues ; 
 int /*<<< orphan*/  action__mes_unmap_queues__reset_queues ; 
 unsigned int engine_sel__mes_unmap_queues__compute ; 
 int /*<<< orphan*/  engine_sel__mes_unmap_queues__sdma0 ; 
 void* extended_engine_sel__mes_unmap_queues__legacy_engine_sel ; 
 void* extended_engine_sel__mes_unmap_queues__sdma0_to_7_sel ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_build_pm4_header (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_sel__mes_unmap_queues__perform_request_on_pasid_queues ; 
 int /*<<< orphan*/  queue_sel__mes_unmap_queues__perform_request_on_specified_queues ; 
 int /*<<< orphan*/  queue_sel__mes_unmap_queues__unmap_all_non_static_queues ; 
 int /*<<< orphan*/  queue_sel__mes_unmap_queues__unmap_all_queues ; 

__attribute__((used)) static int pm_unmap_queues_v9(struct packet_manager *pm, uint32_t *buffer,
			enum kfd_queue_type type,
			enum kfd_unmap_queues_filter filter,
			uint32_t filter_param, bool reset,
			unsigned int sdma_engine)
{
	struct pm4_mes_unmap_queues *packet;

	packet = (struct pm4_mes_unmap_queues *)buffer;
	memset(buffer, 0, sizeof(struct pm4_mes_unmap_queues));

	packet->header.u32All = pm_build_pm4_header(IT_UNMAP_QUEUES,
					sizeof(struct pm4_mes_unmap_queues));
	switch (type) {
	case KFD_QUEUE_TYPE_COMPUTE:
	case KFD_QUEUE_TYPE_DIQ:
		packet->bitfields2.extended_engine_sel =
			extended_engine_sel__mes_unmap_queues__legacy_engine_sel;
		packet->bitfields2.engine_sel =
			engine_sel__mes_unmap_queues__compute;
		break;
	case KFD_QUEUE_TYPE_SDMA:
	case KFD_QUEUE_TYPE_SDMA_XGMI:
		if (sdma_engine < 2) {
			packet->bitfields2.extended_engine_sel =
				extended_engine_sel__mes_unmap_queues__legacy_engine_sel;
			packet->bitfields2.engine_sel =
				engine_sel__mes_unmap_queues__sdma0 + sdma_engine;
		} else {
			packet->bitfields2.extended_engine_sel =
				extended_engine_sel__mes_unmap_queues__sdma0_to_7_sel;
			packet->bitfields2.engine_sel = sdma_engine;
		}
		break;
	default:
		WARN(1, "queue type %d", type);
		return -EINVAL;
	}

	if (reset)
		packet->bitfields2.action =
			action__mes_unmap_queues__reset_queues;
	else
		packet->bitfields2.action =
			action__mes_unmap_queues__preempt_queues;

	switch (filter) {
	case KFD_UNMAP_QUEUES_FILTER_SINGLE_QUEUE:
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__perform_request_on_specified_queues;
		packet->bitfields2.num_queues = 1;
		packet->bitfields3b.doorbell_offset0 = filter_param;
		break;
	case KFD_UNMAP_QUEUES_FILTER_BY_PASID:
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__perform_request_on_pasid_queues;
		packet->bitfields3a.pasid = filter_param;
		break;
	case KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES:
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__unmap_all_queues;
		break;
	case KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES:
		/* in this case, we do not preempt static queues */
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__unmap_all_non_static_queues;
		break;
	default:
		WARN(1, "filter %d", filter);
		return -EINVAL;
	}

	return 0;

}
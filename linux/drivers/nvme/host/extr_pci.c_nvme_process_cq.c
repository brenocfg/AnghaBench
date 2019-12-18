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
typedef  scalar_t__ u16 ;
struct nvme_queue {scalar_t__ cq_head; TYPE_1__* cqes; } ;
struct TYPE_2__ {unsigned int command_id; } ;

/* Variables and functions */
 scalar_t__ nvme_cqe_pending (struct nvme_queue*) ; 
 int /*<<< orphan*/  nvme_ring_cq_doorbell (struct nvme_queue*) ; 
 int /*<<< orphan*/  nvme_update_cq_head (struct nvme_queue*) ; 

__attribute__((used)) static inline int nvme_process_cq(struct nvme_queue *nvmeq, u16 *start,
				  u16 *end, unsigned int tag)
{
	int found = 0;

	*start = nvmeq->cq_head;
	while (nvme_cqe_pending(nvmeq)) {
		if (tag == -1U || nvmeq->cqes[nvmeq->cq_head].command_id == tag)
			found++;
		nvme_update_cq_head(nvmeq);
	}
	*end = nvmeq->cq_head;

	if (*start != *end)
		nvme_ring_cq_doorbell(nvmeq);
	return found;
}
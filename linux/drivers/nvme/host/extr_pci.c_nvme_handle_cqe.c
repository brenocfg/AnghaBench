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
typedef  size_t u16 ;
struct request {int dummy; } ;
struct nvme_queue {scalar_t__ q_depth; scalar_t__ qid; int /*<<< orphan*/  sq_tail; int /*<<< orphan*/ * tags; TYPE_1__* dev; struct nvme_completion* cqes; } ;
struct nvme_completion {scalar_t__ command_id; int /*<<< orphan*/  result; int /*<<< orphan*/  status; int /*<<< orphan*/  sq_head; int /*<<< orphan*/  sq_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {TYPE_2__ ctrl; } ;

/* Variables and functions */
 scalar_t__ NVME_AQ_BLK_MQ_DEPTH ; 
 struct request* blk_mq_tag_to_rq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_complete_async_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nvme_sq (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void nvme_handle_cqe(struct nvme_queue *nvmeq, u16 idx)
{
	volatile struct nvme_completion *cqe = &nvmeq->cqes[idx];
	struct request *req;

	if (unlikely(cqe->command_id >= nvmeq->q_depth)) {
		dev_warn(nvmeq->dev->ctrl.device,
			"invalid id %d completed on queue %d\n",
			cqe->command_id, le16_to_cpu(cqe->sq_id));
		return;
	}

	/*
	 * AEN requests are special as they don't time out and can
	 * survive any kind of queue freeze and often don't respond to
	 * aborts.  We don't even bother to allocate a struct request
	 * for them but rather special case them here.
	 */
	if (unlikely(nvmeq->qid == 0 &&
			cqe->command_id >= NVME_AQ_BLK_MQ_DEPTH)) {
		nvme_complete_async_event(&nvmeq->dev->ctrl,
				cqe->status, &cqe->result);
		return;
	}

	req = blk_mq_tag_to_rq(*nvmeq->tags, cqe->command_id);
	trace_nvme_sq(req, cqe->sq_head, nvmeq->sq_tail);
	nvme_end_request(req, cqe->status, cqe->result);
}
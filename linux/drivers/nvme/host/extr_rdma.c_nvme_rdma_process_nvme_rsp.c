#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct nvme_rdma_request {int /*<<< orphan*/  result; int /*<<< orphan*/  status; int /*<<< orphan*/  ref; TYPE_4__* mr; } ;
struct nvme_rdma_queue {TYPE_5__* ctrl; TYPE_1__* qp; } ;
struct nvme_completion {scalar_t__ command_id; int /*<<< orphan*/  result; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {scalar_t__ invalidate_rkey; } ;
struct ib_wc {int wc_flags; TYPE_2__ ex; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct TYPE_10__ {TYPE_3__ ctrl; } ;
struct TYPE_9__ {scalar_t__ rkey; } ;
struct TYPE_6__ {int qp_num; } ;

/* Variables and functions */
 int IB_WC_WITH_INVALIDATE ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 struct request* blk_mq_tag_to_rq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  nvme_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_error_recovery (TYPE_5__*) ; 
 int nvme_rdma_inv_rkey (struct nvme_rdma_queue*,struct nvme_rdma_request*) ; 
 int /*<<< orphan*/  nvme_rdma_tagset (struct nvme_rdma_queue*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvme_rdma_process_nvme_rsp(struct nvme_rdma_queue *queue,
		struct nvme_completion *cqe, struct ib_wc *wc)
{
	struct request *rq;
	struct nvme_rdma_request *req;

	rq = blk_mq_tag_to_rq(nvme_rdma_tagset(queue), cqe->command_id);
	if (!rq) {
		dev_err(queue->ctrl->ctrl.device,
			"tag 0x%x on QP %#x not found\n",
			cqe->command_id, queue->qp->qp_num);
		nvme_rdma_error_recovery(queue->ctrl);
		return;
	}
	req = blk_mq_rq_to_pdu(rq);

	req->status = cqe->status;
	req->result = cqe->result;

	if (wc->wc_flags & IB_WC_WITH_INVALIDATE) {
		if (unlikely(wc->ex.invalidate_rkey != req->mr->rkey)) {
			dev_err(queue->ctrl->ctrl.device,
				"Bogus remote invalidation for rkey %#x\n",
				req->mr->rkey);
			nvme_rdma_error_recovery(queue->ctrl);
		}
	} else if (req->mr) {
		int ret;

		ret = nvme_rdma_inv_rkey(queue, req);
		if (unlikely(ret < 0)) {
			dev_err(queue->ctrl->ctrl.device,
				"Queueing INV WR for rkey %#x failed (%d)\n",
				req->mr->rkey, ret);
			nvme_rdma_error_recovery(queue->ctrl);
		}
		/* the local invalidation completion will end the request */
		return;
	}

	if (refcount_dec_and_test(&req->ref))
		nvme_end_request(rq, req->status, req->result);
}
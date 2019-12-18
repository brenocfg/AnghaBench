#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * private; int /*<<< orphan*/ * first_sgl; } ;
struct TYPE_6__ {TYPE_1__ fcp_req; } ;
struct nvme_fcp_op_w_sgl {int /*<<< orphan*/ * priv; TYPE_3__ op; int /*<<< orphan*/ * sgl; } ;
struct nvme_fc_queue {int /*<<< orphan*/  rqcnt; } ;
struct blk_mq_tag_set {struct nvme_fc_ctrl* driver_data; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  ctrl; struct nvme_fc_queue* queues; struct blk_mq_tag_set tag_set; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int __nvme_fc_init_request (struct nvme_fc_ctrl*,struct nvme_fc_queue*,TYPE_3__*,struct request*,int /*<<< orphan*/ ) ; 
 struct nvme_fcp_op_w_sgl* blk_mq_rq_to_pdu (struct request*) ; 
 TYPE_2__* nvme_req (struct request*) ; 

__attribute__((used)) static int
nvme_fc_init_request(struct blk_mq_tag_set *set, struct request *rq,
		unsigned int hctx_idx, unsigned int numa_node)
{
	struct nvme_fc_ctrl *ctrl = set->driver_data;
	struct nvme_fcp_op_w_sgl *op = blk_mq_rq_to_pdu(rq);
	int queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	struct nvme_fc_queue *queue = &ctrl->queues[queue_idx];
	int res;

	res = __nvme_fc_init_request(ctrl, queue, &op->op, rq, queue->rqcnt++);
	if (res)
		return res;
	op->op.fcp_req.first_sgl = &op->sgl[0];
	op->op.fcp_req.private = &op->priv[0];
	nvme_req(rq)->ctrl = &ctrl->ctrl;
	return res;
}
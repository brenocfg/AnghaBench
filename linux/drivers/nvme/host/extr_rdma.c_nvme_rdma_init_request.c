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
struct request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct nvme_rdma_request {struct nvme_rdma_queue* queue; TYPE_1__ sqe; } ;
struct nvme_rdma_queue {int dummy; } ;
struct blk_mq_tag_set {struct nvme_rdma_ctrl* driver_data; } ;
struct nvme_rdma_ctrl {int /*<<< orphan*/  ctrl; struct nvme_rdma_queue* queues; struct blk_mq_tag_set tag_set; } ;
struct nvme_command {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* nvme_req (struct request*) ; 

__attribute__((used)) static int nvme_rdma_init_request(struct blk_mq_tag_set *set,
		struct request *rq, unsigned int hctx_idx,
		unsigned int numa_node)
{
	struct nvme_rdma_ctrl *ctrl = set->driver_data;
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	int queue_idx = (set == &ctrl->tag_set) ? hctx_idx + 1 : 0;
	struct nvme_rdma_queue *queue = &ctrl->queues[queue_idx];

	nvme_req(rq)->ctrl = &ctrl->ctrl;
	req->sqe.data = kzalloc(sizeof(struct nvme_command), GFP_KERNEL);
	if (!req->sqe.data)
		return -ENOMEM;

	req->queue = queue;

	return 0;
}
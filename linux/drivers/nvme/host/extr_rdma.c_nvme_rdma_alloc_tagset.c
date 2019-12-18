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
struct scatterlist {int dummy; } ;
struct nvme_rdma_request {int dummy; } ;
struct blk_mq_tag_set {int reserved_tags; int cmd_size; int nr_hw_queues; int nr_maps; int /*<<< orphan*/  timeout; struct nvme_rdma_ctrl* driver_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  numa_node; scalar_t__ queue_depth; int /*<<< orphan*/ * ops; } ;
struct nvme_rdma_ctrl {struct blk_mq_tag_set tag_set; struct blk_mq_tag_set admin_tag_set; } ;
struct nvme_ctrl {int queue_count; TYPE_1__* opts; int /*<<< orphan*/  numa_node; scalar_t__ sqsize; } ;
struct TYPE_2__ {scalar_t__ nr_poll_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMIN_TIMEOUT ; 
 int /*<<< orphan*/  BLK_MQ_F_NO_SCHED ; 
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 struct blk_mq_tag_set* ERR_PTR (int) ; 
 int HCTX_MAX_TYPES ; 
 scalar_t__ NVME_AQ_MQ_TAG_DEPTH ; 
 int /*<<< orphan*/  NVME_IO_TIMEOUT ; 
 int SG_CHUNK_SIZE ; 
 int blk_mq_alloc_tag_set (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  memset (struct blk_mq_tag_set*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_rdma_admin_mq_ops ; 
 int /*<<< orphan*/  nvme_rdma_mq_ops ; 
 struct nvme_rdma_ctrl* to_rdma_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static struct blk_mq_tag_set *nvme_rdma_alloc_tagset(struct nvme_ctrl *nctrl,
		bool admin)
{
	struct nvme_rdma_ctrl *ctrl = to_rdma_ctrl(nctrl);
	struct blk_mq_tag_set *set;
	int ret;

	if (admin) {
		set = &ctrl->admin_tag_set;
		memset(set, 0, sizeof(*set));
		set->ops = &nvme_rdma_admin_mq_ops;
		set->queue_depth = NVME_AQ_MQ_TAG_DEPTH;
		set->reserved_tags = 2; /* connect + keep-alive */
		set->numa_node = nctrl->numa_node;
		set->cmd_size = sizeof(struct nvme_rdma_request) +
			SG_CHUNK_SIZE * sizeof(struct scatterlist);
		set->driver_data = ctrl;
		set->nr_hw_queues = 1;
		set->timeout = ADMIN_TIMEOUT;
		set->flags = BLK_MQ_F_NO_SCHED;
	} else {
		set = &ctrl->tag_set;
		memset(set, 0, sizeof(*set));
		set->ops = &nvme_rdma_mq_ops;
		set->queue_depth = nctrl->sqsize + 1;
		set->reserved_tags = 1; /* fabric connect */
		set->numa_node = nctrl->numa_node;
		set->flags = BLK_MQ_F_SHOULD_MERGE;
		set->cmd_size = sizeof(struct nvme_rdma_request) +
			SG_CHUNK_SIZE * sizeof(struct scatterlist);
		set->driver_data = ctrl;
		set->nr_hw_queues = nctrl->queue_count - 1;
		set->timeout = NVME_IO_TIMEOUT;
		set->nr_maps = nctrl->opts->nr_poll_queues ? HCTX_MAX_TYPES : 2;
	}

	ret = blk_mq_alloc_tag_set(set);
	if (ret)
		return ERR_PTR(ret);

	return set;
}
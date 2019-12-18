#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct nvme_loop_iod {int dummy; } ;
struct TYPE_11__ {int reserved_tags; int cmd_size; int nr_hw_queues; int /*<<< orphan*/  flags; int /*<<< orphan*/  timeout; struct nvme_loop_ctrl* driver_data; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {int queue_count; int max_hw_sectors; void* fabrics_q; void* admin_q; TYPE_5__* admin_tagset; } ;
struct nvme_loop_ctrl {TYPE_1__* queues; TYPE_5__ admin_tag_set; TYPE_2__ ctrl; } ;
struct TYPE_9__ {int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  flags; struct nvme_loop_ctrl* ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMIN_TIMEOUT ; 
 int /*<<< orphan*/  BLK_MQ_F_NO_SCHED ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  NVME_AQ_MQ_TAG_DEPTH ; 
 int NVME_LOOP_MAX_SEGMENTS ; 
 int /*<<< orphan*/  NVME_LOOP_Q_LIVE ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (void*) ; 
 int SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  blk_cleanup_queue (void*) ; 
 int blk_mq_alloc_tag_set (TYPE_5__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_5__*) ; 
 void* blk_mq_init_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (void*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int nvme_enable_ctrl (TYPE_2__*) ; 
 int nvme_init_identify (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_loop_admin_mq_ops ; 
 int /*<<< orphan*/  nvmet_sq_destroy (int /*<<< orphan*/ *) ; 
 int nvmet_sq_init (int /*<<< orphan*/ *) ; 
 int nvmf_connect_admin_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_loop_configure_admin_queue(struct nvme_loop_ctrl *ctrl)
{
	int error;

	memset(&ctrl->admin_tag_set, 0, sizeof(ctrl->admin_tag_set));
	ctrl->admin_tag_set.ops = &nvme_loop_admin_mq_ops;
	ctrl->admin_tag_set.queue_depth = NVME_AQ_MQ_TAG_DEPTH;
	ctrl->admin_tag_set.reserved_tags = 2; /* connect + keep-alive */
	ctrl->admin_tag_set.numa_node = NUMA_NO_NODE;
	ctrl->admin_tag_set.cmd_size = sizeof(struct nvme_loop_iod) +
		SG_CHUNK_SIZE * sizeof(struct scatterlist);
	ctrl->admin_tag_set.driver_data = ctrl;
	ctrl->admin_tag_set.nr_hw_queues = 1;
	ctrl->admin_tag_set.timeout = ADMIN_TIMEOUT;
	ctrl->admin_tag_set.flags = BLK_MQ_F_NO_SCHED;

	ctrl->queues[0].ctrl = ctrl;
	error = nvmet_sq_init(&ctrl->queues[0].nvme_sq);
	if (error)
		return error;
	ctrl->ctrl.queue_count = 1;

	error = blk_mq_alloc_tag_set(&ctrl->admin_tag_set);
	if (error)
		goto out_free_sq;
	ctrl->ctrl.admin_tagset = &ctrl->admin_tag_set;

	ctrl->ctrl.fabrics_q = blk_mq_init_queue(&ctrl->admin_tag_set);
	if (IS_ERR(ctrl->ctrl.fabrics_q)) {
		error = PTR_ERR(ctrl->ctrl.fabrics_q);
		goto out_free_tagset;
	}

	ctrl->ctrl.admin_q = blk_mq_init_queue(&ctrl->admin_tag_set);
	if (IS_ERR(ctrl->ctrl.admin_q)) {
		error = PTR_ERR(ctrl->ctrl.admin_q);
		goto out_cleanup_fabrics_q;
	}

	error = nvmf_connect_admin_queue(&ctrl->ctrl);
	if (error)
		goto out_cleanup_queue;

	set_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[0].flags);

	error = nvme_enable_ctrl(&ctrl->ctrl);
	if (error)
		goto out_cleanup_queue;

	ctrl->ctrl.max_hw_sectors =
		(NVME_LOOP_MAX_SEGMENTS - 1) << (PAGE_SHIFT - 9);

	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	error = nvme_init_identify(&ctrl->ctrl);
	if (error)
		goto out_cleanup_queue;

	return 0;

out_cleanup_queue:
	blk_cleanup_queue(ctrl->ctrl.admin_q);
out_cleanup_fabrics_q:
	blk_cleanup_queue(ctrl->ctrl.fabrics_q);
out_free_tagset:
	blk_mq_free_tag_set(&ctrl->admin_tag_set);
out_free_sq:
	nvmet_sq_destroy(&ctrl->queues[0].nvme_sq);
	return error;
}
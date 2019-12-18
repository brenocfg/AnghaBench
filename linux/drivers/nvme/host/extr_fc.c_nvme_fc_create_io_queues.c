#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nvmf_ctrl_options {unsigned int nr_io_queues; int /*<<< orphan*/  queue_size; } ;
struct nvme_fcp_op_w_sgl {int dummy; } ;
struct TYPE_10__ {unsigned int queue_count; TYPE_4__* tagset; int /*<<< orphan*/  connect_q; scalar_t__ sqsize; int /*<<< orphan*/  numa_node; struct nvmf_ctrl_options* opts; int /*<<< orphan*/  device; } ;
struct TYPE_11__ {int reserved_tags; int nr_hw_queues; int /*<<< orphan*/  timeout; struct nvme_fc_ctrl* driver_data; int /*<<< orphan*/  cmd_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/ * ops; } ;
struct nvme_fc_ctrl {int ioq_live; TYPE_3__ ctrl; TYPE_4__ tag_set; TYPE_2__* lport; } ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  fcprqst_priv_sz; int /*<<< orphan*/  max_hw_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_IO_TIMEOUT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int blk_mq_alloc_tag_set (TYPE_4__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_4__*) ; 
 int /*<<< orphan*/  blk_mq_init_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int nvme_fc_connect_io_queues (struct nvme_fc_ctrl*,scalar_t__) ; 
 int nvme_fc_create_hw_io_queues (struct nvme_fc_ctrl*,scalar_t__) ; 
 int /*<<< orphan*/  nvme_fc_delete_hw_io_queues (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_free_io_queues (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_init_io_queues (struct nvme_fc_ctrl*) ; 
 int /*<<< orphan*/  nvme_fc_mq_ops ; 
 int nvme_set_queue_count (TYPE_3__*,unsigned int*) ; 
 int /*<<< orphan*/  priv ; 
 int /*<<< orphan*/  struct_size (struct nvme_fcp_op_w_sgl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvme_fc_create_io_queues(struct nvme_fc_ctrl *ctrl)
{
	struct nvmf_ctrl_options *opts = ctrl->ctrl.opts;
	unsigned int nr_io_queues;
	int ret;

	nr_io_queues = min(min(opts->nr_io_queues, num_online_cpus()),
				ctrl->lport->ops->max_hw_queues);
	ret = nvme_set_queue_count(&ctrl->ctrl, &nr_io_queues);
	if (ret) {
		dev_info(ctrl->ctrl.device,
			"set_queue_count failed: %d\n", ret);
		return ret;
	}

	ctrl->ctrl.queue_count = nr_io_queues + 1;
	if (!nr_io_queues)
		return 0;

	nvme_fc_init_io_queues(ctrl);

	memset(&ctrl->tag_set, 0, sizeof(ctrl->tag_set));
	ctrl->tag_set.ops = &nvme_fc_mq_ops;
	ctrl->tag_set.queue_depth = ctrl->ctrl.opts->queue_size;
	ctrl->tag_set.reserved_tags = 1; /* fabric connect */
	ctrl->tag_set.numa_node = ctrl->ctrl.numa_node;
	ctrl->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ctrl->tag_set.cmd_size =
		struct_size((struct nvme_fcp_op_w_sgl *)NULL, priv,
			    ctrl->lport->ops->fcprqst_priv_sz);
	ctrl->tag_set.driver_data = ctrl;
	ctrl->tag_set.nr_hw_queues = ctrl->ctrl.queue_count - 1;
	ctrl->tag_set.timeout = NVME_IO_TIMEOUT;

	ret = blk_mq_alloc_tag_set(&ctrl->tag_set);
	if (ret)
		return ret;

	ctrl->ctrl.tagset = &ctrl->tag_set;

	ctrl->ctrl.connect_q = blk_mq_init_queue(&ctrl->tag_set);
	if (IS_ERR(ctrl->ctrl.connect_q)) {
		ret = PTR_ERR(ctrl->ctrl.connect_q);
		goto out_free_tag_set;
	}

	ret = nvme_fc_create_hw_io_queues(ctrl, ctrl->ctrl.sqsize + 1);
	if (ret)
		goto out_cleanup_blk_queue;

	ret = nvme_fc_connect_io_queues(ctrl, ctrl->ctrl.sqsize + 1);
	if (ret)
		goto out_delete_hw_queues;

	ctrl->ioq_live = true;

	return 0;

out_delete_hw_queues:
	nvme_fc_delete_hw_io_queues(ctrl);
out_cleanup_blk_queue:
	blk_cleanup_queue(ctrl->ctrl.connect_q);
out_free_tag_set:
	blk_mq_free_tag_set(&ctrl->tag_set);
	nvme_fc_free_io_queues(ctrl);

	/* force put free routine to ignore io queues */
	ctrl->ctrl.tagset = NULL;

	return ret;
}
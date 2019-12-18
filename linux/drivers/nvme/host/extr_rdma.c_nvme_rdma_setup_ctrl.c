#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sgls; scalar_t__ sqsize; scalar_t__ maxcmd; int queue_count; scalar_t__ state; int /*<<< orphan*/  device; TYPE_1__* opts; scalar_t__ icdoff; } ;
struct nvme_rdma_ctrl {int use_inline_data; int /*<<< orphan*/ * queues; TYPE_2__ ctrl; } ;
struct TYPE_4__ {scalar_t__ queue_size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NVME_CTRL_DELETING ; 
 int /*<<< orphan*/  NVME_CTRL_LIVE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int nvme_change_ctrl_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int nvme_rdma_configure_admin_queue (struct nvme_rdma_ctrl*,int) ; 
 int nvme_rdma_configure_io_queues (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_destroy_admin_queue (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_destroy_io_queues (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_stop_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_start_ctrl (TYPE_2__*) ; 

__attribute__((used)) static int nvme_rdma_setup_ctrl(struct nvme_rdma_ctrl *ctrl, bool new)
{
	int ret = -EINVAL;
	bool changed;

	ret = nvme_rdma_configure_admin_queue(ctrl, new);
	if (ret)
		return ret;

	if (ctrl->ctrl.icdoff) {
		dev_err(ctrl->ctrl.device, "icdoff is not supported!\n");
		goto destroy_admin;
	}

	if (!(ctrl->ctrl.sgls & (1 << 2))) {
		dev_err(ctrl->ctrl.device,
			"Mandatory keyed sgls are not supported!\n");
		goto destroy_admin;
	}

	if (ctrl->ctrl.opts->queue_size > ctrl->ctrl.sqsize + 1) {
		dev_warn(ctrl->ctrl.device,
			"queue_size %zu > ctrl sqsize %u, clamping down\n",
			ctrl->ctrl.opts->queue_size, ctrl->ctrl.sqsize + 1);
	}

	if (ctrl->ctrl.sqsize + 1 > ctrl->ctrl.maxcmd) {
		dev_warn(ctrl->ctrl.device,
			"sqsize %u > ctrl maxcmd %u, clamping down\n",
			ctrl->ctrl.sqsize + 1, ctrl->ctrl.maxcmd);
		ctrl->ctrl.sqsize = ctrl->ctrl.maxcmd - 1;
	}

	if (ctrl->ctrl.sgls & (1 << 20))
		ctrl->use_inline_data = true;

	if (ctrl->ctrl.queue_count > 1) {
		ret = nvme_rdma_configure_io_queues(ctrl, new);
		if (ret)
			goto destroy_admin;
	}

	changed = nvme_change_ctrl_state(&ctrl->ctrl, NVME_CTRL_LIVE);
	if (!changed) {
		/* state change failure is ok if we're in DELETING state */
		WARN_ON_ONCE(ctrl->ctrl.state != NVME_CTRL_DELETING);
		ret = -EINVAL;
		goto destroy_io;
	}

	nvme_start_ctrl(&ctrl->ctrl);
	return 0;

destroy_io:
	if (ctrl->ctrl.queue_count > 1)
		nvme_rdma_destroy_io_queues(ctrl, new);
destroy_admin:
	nvme_rdma_stop_queue(&ctrl->queues[0]);
	nvme_rdma_destroy_admin_queue(ctrl, new);
	return ret;
}
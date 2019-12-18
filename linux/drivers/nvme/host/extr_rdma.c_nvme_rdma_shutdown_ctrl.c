#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  admin_q; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  err_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_disable_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_rdma_teardown_admin_queue (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_teardown_io_queues (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_shutdown_ctrl (TYPE_1__*) ; 

__attribute__((used)) static void nvme_rdma_shutdown_ctrl(struct nvme_rdma_ctrl *ctrl, bool shutdown)
{
	cancel_work_sync(&ctrl->err_work);
	cancel_delayed_work_sync(&ctrl->reconnect_work);

	nvme_rdma_teardown_io_queues(ctrl, shutdown);
	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	if (shutdown)
		nvme_shutdown_ctrl(&ctrl->ctrl);
	else
		nvme_disable_ctrl(&ctrl->ctrl);
	nvme_rdma_teardown_admin_queue(ctrl, shutdown);
}
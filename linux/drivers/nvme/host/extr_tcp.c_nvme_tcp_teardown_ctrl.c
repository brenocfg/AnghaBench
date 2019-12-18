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
struct nvme_ctrl {int /*<<< orphan*/  admin_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  connect_work; int /*<<< orphan*/  err_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_disable_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_shutdown_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_tcp_teardown_admin_queue (struct nvme_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_tcp_teardown_io_queues (struct nvme_ctrl*,int) ; 
 TYPE_1__* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_teardown_ctrl(struct nvme_ctrl *ctrl, bool shutdown)
{
	cancel_work_sync(&to_tcp_ctrl(ctrl)->err_work);
	cancel_delayed_work_sync(&to_tcp_ctrl(ctrl)->connect_work);

	nvme_tcp_teardown_io_queues(ctrl, shutdown);
	blk_mq_quiesce_queue(ctrl->admin_q);
	if (shutdown)
		nvme_shutdown_ctrl(ctrl);
	else
		nvme_disable_ctrl(ctrl);
	nvme_tcp_teardown_admin_queue(ctrl, shutdown);
}
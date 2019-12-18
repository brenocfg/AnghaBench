#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int queue_count; scalar_t__ state; int /*<<< orphan*/  admin_q; } ;
struct nvme_loop_ctrl {int /*<<< orphan*/  admin_tag_set; TYPE_1__ ctrl; int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_LIVE ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  blk_mq_tagset_wait_completed_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_cancel_request ; 
 int /*<<< orphan*/  nvme_loop_destroy_admin_queue (struct nvme_loop_ctrl*) ; 
 int /*<<< orphan*/  nvme_loop_destroy_io_queues (struct nvme_loop_ctrl*) ; 
 int /*<<< orphan*/  nvme_shutdown_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_stop_queues (TYPE_1__*) ; 

__attribute__((used)) static void nvme_loop_shutdown_ctrl(struct nvme_loop_ctrl *ctrl)
{
	if (ctrl->ctrl.queue_count > 1) {
		nvme_stop_queues(&ctrl->ctrl);
		blk_mq_tagset_busy_iter(&ctrl->tag_set,
					nvme_cancel_request, &ctrl->ctrl);
		blk_mq_tagset_wait_completed_request(&ctrl->tag_set);
		nvme_loop_destroy_io_queues(ctrl);
	}

	blk_mq_quiesce_queue(ctrl->ctrl.admin_q);
	if (ctrl->ctrl.state == NVME_CTRL_LIVE)
		nvme_shutdown_ctrl(&ctrl->ctrl);

	blk_mq_tagset_busy_iter(&ctrl->admin_tag_set,
				nvme_cancel_request, &ctrl->ctrl);
	blk_mq_tagset_wait_completed_request(&ctrl->admin_tag_set);
	nvme_loop_destroy_admin_queue(ctrl);
}
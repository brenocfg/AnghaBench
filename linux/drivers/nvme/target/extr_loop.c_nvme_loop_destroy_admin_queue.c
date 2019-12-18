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
struct TYPE_4__ {int /*<<< orphan*/  fabrics_q; int /*<<< orphan*/  admin_q; } ;
struct nvme_loop_ctrl {int /*<<< orphan*/  admin_tag_set; TYPE_2__ ctrl; TYPE_1__* queues; } ;
struct TYPE_3__ {int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_LOOP_Q_LIVE ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_sq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_loop_destroy_admin_queue(struct nvme_loop_ctrl *ctrl)
{
	clear_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[0].flags);
	nvmet_sq_destroy(&ctrl->queues[0].nvme_sq);
	blk_cleanup_queue(ctrl->ctrl.admin_q);
	blk_cleanup_queue(ctrl->ctrl.fabrics_q);
	blk_mq_free_tag_set(&ctrl->admin_tag_set);
}
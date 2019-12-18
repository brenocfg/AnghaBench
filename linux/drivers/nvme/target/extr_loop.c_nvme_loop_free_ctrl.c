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
struct TYPE_2__ {int /*<<< orphan*/  connect_q; } ;
struct nvme_loop_ctrl {struct nvme_loop_ctrl* queues; int /*<<< orphan*/  tag_set; TYPE_1__ ctrl; int /*<<< orphan*/  list; } ;
struct nvme_ctrl {int /*<<< orphan*/  opts; scalar_t__ tagset; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvme_loop_ctrl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_loop_ctrl_mutex ; 
 int /*<<< orphan*/  nvmf_free_options (int /*<<< orphan*/ ) ; 
 struct nvme_loop_ctrl* to_loop_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_loop_free_ctrl(struct nvme_ctrl *nctrl)
{
	struct nvme_loop_ctrl *ctrl = to_loop_ctrl(nctrl);

	if (list_empty(&ctrl->list))
		goto free_ctrl;

	mutex_lock(&nvme_loop_ctrl_mutex);
	list_del(&ctrl->list);
	mutex_unlock(&nvme_loop_ctrl_mutex);

	if (nctrl->tagset) {
		blk_cleanup_queue(ctrl->ctrl.connect_q);
		blk_mq_free_tag_set(&ctrl->tag_set);
	}
	kfree(ctrl->queues);
	nvmf_free_options(nctrl->opts);
free_ctrl:
	kfree(ctrl);
}
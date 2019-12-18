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
struct nvme_ctrl {TYPE_2__* ops; int /*<<< orphan*/  reset_work; TYPE_1__* opts; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* delete_ctrl ) (struct nvme_ctrl*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  subsysnqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_put_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_remove_namespaces (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_stop_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_uninit_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  stub1 (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_do_delete_ctrl(struct nvme_ctrl *ctrl)
{
	dev_info(ctrl->device,
		 "Removing ctrl: NQN \"%s\"\n", ctrl->opts->subsysnqn);

	flush_work(&ctrl->reset_work);
	nvme_stop_ctrl(ctrl);
	nvme_remove_namespaces(ctrl);
	ctrl->ops->delete_ctrl(ctrl);
	nvme_uninit_ctrl(ctrl);
	nvme_put_ctrl(ctrl);
}
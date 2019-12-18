#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NVME_CTRL_DELETING ; 
 int /*<<< orphan*/  nvme_change_ctrl_state (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_do_delete_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_get_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_put_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static int nvme_delete_ctrl_sync(struct nvme_ctrl *ctrl)
{
	int ret = 0;

	/*
	 * Keep a reference until nvme_do_delete_ctrl() complete,
	 * since ->delete_ctrl can free the controller.
	 */
	nvme_get_ctrl(ctrl);
	if (!nvme_change_ctrl_state(ctrl, NVME_CTRL_DELETING))
		ret = -EBUSY;
	if (!ret)
		nvme_do_delete_ctrl(ctrl);
	nvme_put_ctrl(ctrl);
	return ret;
}
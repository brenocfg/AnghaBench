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
struct nvme_ctrl {scalar_t__ state; int /*<<< orphan*/  reset_work; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ NVME_CTRL_RESETTING ; 
 int /*<<< orphan*/  nvme_reset_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nvme_try_sched_reset(struct nvme_ctrl *ctrl)
{
	if (ctrl->state != NVME_CTRL_RESETTING)
		return -EBUSY;
	if (!queue_work(nvme_reset_wq, &ctrl->reset_work))
		return -EBUSY;
	return 0;
}
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
struct nvme_ctrl {scalar_t__ state; int /*<<< orphan*/  state_wq; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_RESETTING ; 
 scalar_t__ nvme_change_ctrl_state (struct nvme_ctrl*,scalar_t__) ; 
 scalar_t__ nvme_state_terminal (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

bool nvme_wait_reset(struct nvme_ctrl *ctrl)
{
	wait_event(ctrl->state_wq,
		   nvme_change_ctrl_state(ctrl, NVME_CTRL_RESETTING) ||
		   nvme_state_terminal(ctrl));
	return ctrl->state == NVME_CTRL_RESETTING;
}
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
struct nvme_ctrl {int state; } ;

/* Variables and functions */
#define  NVME_CTRL_CONNECTING 133 
#define  NVME_CTRL_DEAD 132 
#define  NVME_CTRL_DELETING 131 
#define  NVME_CTRL_LIVE 130 
#define  NVME_CTRL_NEW 129 
#define  NVME_CTRL_RESETTING 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static bool nvme_state_terminal(struct nvme_ctrl *ctrl)
{
	switch (ctrl->state) {
	case NVME_CTRL_NEW:
	case NVME_CTRL_LIVE:
	case NVME_CTRL_RESETTING:
	case NVME_CTRL_CONNECTING:
		return false;
	case NVME_CTRL_DELETING:
	case NVME_CTRL_DEAD:
		return true;
	default:
		WARN_ONCE(1, "Unhandled ctrl state:%d", ctrl->state);
		return true;
	}
}
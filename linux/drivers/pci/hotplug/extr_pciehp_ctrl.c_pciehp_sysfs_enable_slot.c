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
struct hotplug_slot {int dummy; } ;
struct controller {int state; int request_result; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  requester; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 133 
#define  BLINKINGON_STATE 132 
 int ENODEV ; 
#define  OFF_STATE 131 
#define  ON_STATE 130 
 int /*<<< orphan*/  PCI_EXP_SLTSTA_PDC ; 
#define  POWEROFF_STATE 129 
#define  POWERON_STATE 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_request (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct controller*) ; 
 struct controller* to_ctrl (struct hotplug_slot*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int pciehp_sysfs_enable_slot(struct hotplug_slot *hotplug_slot)
{
	struct controller *ctrl = to_ctrl(hotplug_slot);

	mutex_lock(&ctrl->state_lock);
	switch (ctrl->state) {
	case BLINKINGON_STATE:
	case OFF_STATE:
		mutex_unlock(&ctrl->state_lock);
		/*
		 * The IRQ thread becomes a no-op if the user pulls out the
		 * card before the thread wakes up, so initialize to -ENODEV.
		 */
		ctrl->request_result = -ENODEV;
		pciehp_request(ctrl, PCI_EXP_SLTSTA_PDC);
		wait_event(ctrl->requester,
			   !atomic_read(&ctrl->pending_events));
		return ctrl->request_result;
	case POWERON_STATE:
		ctrl_info(ctrl, "Slot(%s): Already in powering on state\n",
			  slot_name(ctrl));
		break;
	case BLINKINGOFF_STATE:
	case ON_STATE:
	case POWEROFF_STATE:
		ctrl_info(ctrl, "Slot(%s): Already enabled\n",
			  slot_name(ctrl));
		break;
	default:
		ctrl_err(ctrl, "Slot(%s): Invalid state %#x\n",
			 slot_name(ctrl), ctrl->state);
		break;
	}
	mutex_unlock(&ctrl->state_lock);

	return -ENODEV;
}
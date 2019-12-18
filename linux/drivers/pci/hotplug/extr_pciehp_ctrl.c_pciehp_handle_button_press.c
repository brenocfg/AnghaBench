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
struct controller {int state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  button_work; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 131 
#define  BLINKINGON_STATE 130 
 int HZ ; 
#define  OFF_STATE 129 
#define  ON_STATE 128 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_ATTN_IND_OFF ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_PWR_IND_BLINK ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_PWR_IND_OFF ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_PWR_IND_ON ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_set_indicators (struct controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slot_name (struct controller*) ; 

void pciehp_handle_button_press(struct controller *ctrl)
{
	mutex_lock(&ctrl->state_lock);
	switch (ctrl->state) {
	case OFF_STATE:
	case ON_STATE:
		if (ctrl->state == ON_STATE) {
			ctrl->state = BLINKINGOFF_STATE;
			ctrl_info(ctrl, "Slot(%s): Powering off due to button press\n",
				  slot_name(ctrl));
		} else {
			ctrl->state = BLINKINGON_STATE;
			ctrl_info(ctrl, "Slot(%s) Powering on due to button press\n",
				  slot_name(ctrl));
		}
		/* blink power indicator and turn off attention */
		pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_BLINK,
				      PCI_EXP_SLTCTL_ATTN_IND_OFF);
		schedule_delayed_work(&ctrl->button_work, 5 * HZ);
		break;
	case BLINKINGOFF_STATE:
	case BLINKINGON_STATE:
		/*
		 * Cancel if we are still blinking; this means that we
		 * press the attention again before the 5 sec. limit
		 * expires to cancel hot-add or hot-remove
		 */
		ctrl_info(ctrl, "Slot(%s): Button cancel\n", slot_name(ctrl));
		cancel_delayed_work(&ctrl->button_work);
		if (ctrl->state == BLINKINGOFF_STATE) {
			ctrl->state = ON_STATE;
			pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_ON,
					      PCI_EXP_SLTCTL_ATTN_IND_OFF);
		} else {
			ctrl->state = OFF_STATE;
			pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
					      PCI_EXP_SLTCTL_ATTN_IND_OFF);
		}
		ctrl_info(ctrl, "Slot(%s): Action canceled due to button press\n",
			  slot_name(ctrl));
		break;
	default:
		ctrl_err(ctrl, "Slot(%s): Ignoring invalid state %#x\n",
			 slot_name(ctrl), ctrl->state);
		break;
	}
	mutex_unlock(&ctrl->state_lock);
}
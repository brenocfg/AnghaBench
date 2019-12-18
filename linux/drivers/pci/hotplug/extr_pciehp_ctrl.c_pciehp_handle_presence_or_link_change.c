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
typedef  int u32 ;
struct controller {int state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  request_result; int /*<<< orphan*/  button_work; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 131 
#define  BLINKINGON_STATE 130 
#define  OFF_STATE 129 
#define  ON_STATE 128 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 int POWEROFF_STATE ; 
 int POWERON_STATE ; 
 int /*<<< orphan*/  SURPRISE_REMOVAL ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pciehp_card_present (struct controller*) ; 
 int pciehp_check_link_active (struct controller*) ; 
 int /*<<< orphan*/  pciehp_disable_slot (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_enable_slot (struct controller*) ; 
 int /*<<< orphan*/  slot_name (struct controller*) ; 

void pciehp_handle_presence_or_link_change(struct controller *ctrl, u32 events)
{
	bool present, link_active;

	/*
	 * If the slot is on and presence or link has changed, turn it off.
	 * Even if it's occupied again, we cannot assume the card is the same.
	 */
	mutex_lock(&ctrl->state_lock);
	switch (ctrl->state) {
	case BLINKINGOFF_STATE:
		cancel_delayed_work(&ctrl->button_work);
		/* fall through */
	case ON_STATE:
		ctrl->state = POWEROFF_STATE;
		mutex_unlock(&ctrl->state_lock);
		if (events & PCI_EXP_SLTSTA_DLLSC)
			ctrl_info(ctrl, "Slot(%s): Link Down\n",
				  slot_name(ctrl));
		if (events & PCI_EXP_SLTSTA_PDC)
			ctrl_info(ctrl, "Slot(%s): Card not present\n",
				  slot_name(ctrl));
		pciehp_disable_slot(ctrl, SURPRISE_REMOVAL);
		break;
	default:
		mutex_unlock(&ctrl->state_lock);
		break;
	}

	/* Turn the slot on if it's occupied or link is up */
	mutex_lock(&ctrl->state_lock);
	present = pciehp_card_present(ctrl);
	link_active = pciehp_check_link_active(ctrl);
	if (!present && !link_active) {
		mutex_unlock(&ctrl->state_lock);
		return;
	}

	switch (ctrl->state) {
	case BLINKINGON_STATE:
		cancel_delayed_work(&ctrl->button_work);
		/* fall through */
	case OFF_STATE:
		ctrl->state = POWERON_STATE;
		mutex_unlock(&ctrl->state_lock);
		if (present)
			ctrl_info(ctrl, "Slot(%s): Card present\n",
				  slot_name(ctrl));
		if (link_active)
			ctrl_info(ctrl, "Slot(%s): Link Up\n",
				  slot_name(ctrl));
		ctrl->request_result = pciehp_enable_slot(ctrl);
		break;
	default:
		mutex_unlock(&ctrl->state_lock);
		break;
	}
}
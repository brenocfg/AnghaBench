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
struct controller {int state; int /*<<< orphan*/  request_result; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  button_work; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 129 
#define  BLINKINGON_STATE 128 
 int POWEROFF_STATE ; 
 int /*<<< orphan*/  SAFE_REMOVAL ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_disable_slot (struct controller*,int /*<<< orphan*/ ) ; 

void pciehp_handle_disable_request(struct controller *ctrl)
{
	mutex_lock(&ctrl->state_lock);
	switch (ctrl->state) {
	case BLINKINGON_STATE:
	case BLINKINGOFF_STATE:
		cancel_delayed_work(&ctrl->button_work);
		break;
	}
	ctrl->state = POWEROFF_STATE;
	mutex_unlock(&ctrl->state_lock);

	ctrl->request_result = pciehp_disable_slot(ctrl, SAFE_REMOVAL);
}
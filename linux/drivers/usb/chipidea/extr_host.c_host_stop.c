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
struct usb_hcd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * host; } ;
struct ci_hdrc {TYPE_2__* platdata; TYPE_1__ otg; struct usb_hcd* hcd; int /*<<< orphan*/  irq; int /*<<< orphan*/  role; } ;
struct TYPE_4__ {int flags; scalar_t__ pins_default; int /*<<< orphan*/  pctl; scalar_t__ pins_host; scalar_t__ reg_vbus; int /*<<< orphan*/  (* notify_event ) (struct ci_hdrc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CI_HDRC_CONTROLLER_STOPPED_EVENT ; 
 int CI_HDRC_TURN_VBUS_EARLY_ON ; 
 int /*<<< orphan*/  CI_ROLE_END ; 
 int /*<<< orphan*/  ci_otg_is_fsm_mode (struct ci_hdrc*) ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ci_hdrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void host_stop(struct ci_hdrc *ci)
{
	struct usb_hcd *hcd = ci->hcd;

	if (hcd) {
		if (ci->platdata->notify_event)
			ci->platdata->notify_event(ci,
				CI_HDRC_CONTROLLER_STOPPED_EVENT);
		usb_remove_hcd(hcd);
		ci->role = CI_ROLE_END;
		synchronize_irq(ci->irq);
		usb_put_hcd(hcd);
		if (ci->platdata->reg_vbus && !ci_otg_is_fsm_mode(ci) &&
			(ci->platdata->flags & CI_HDRC_TURN_VBUS_EARLY_ON))
				regulator_disable(ci->platdata->reg_vbus);
	}
	ci->hcd = NULL;
	ci->otg.host = NULL;

	if (ci->platdata->pins_host && ci->platdata->pins_default)
		pinctrl_select_state(ci->platdata->pctl,
				     ci->platdata->pins_default);
}
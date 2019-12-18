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
struct TYPE_3__ {int /*<<< orphan*/  root_hub; int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_2__* primary_hcd; int /*<<< orphan*/  died_work; TYPE_1__ self; int /*<<< orphan*/  flags; scalar_t__ rh_registered; struct usb_hcd* shared_hcd; } ;
struct TYPE_4__ {int /*<<< orphan*/  died_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_DEAD ; 
 int /*<<< orphan*/  HCD_FLAG_POLL_RH ; 
 int /*<<< orphan*/  HCD_FLAG_RH_RUNNING ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hcd_root_hub_lock ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_kick_hub_wq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_device_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usb_hc_died (struct usb_hcd *hcd)
{
	unsigned long flags;

	dev_err (hcd->self.controller, "HC died; cleaning up\n");

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
	set_bit(HCD_FLAG_DEAD, &hcd->flags);
	if (hcd->rh_registered) {
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

		/* make hub_wq clean up old urbs and devices */
		usb_set_device_state (hcd->self.root_hub,
				USB_STATE_NOTATTACHED);
		usb_kick_hub_wq(hcd->self.root_hub);
	}
	if (usb_hcd_is_primary_hcd(hcd) && hcd->shared_hcd) {
		hcd = hcd->shared_hcd;
		clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
		set_bit(HCD_FLAG_DEAD, &hcd->flags);
		if (hcd->rh_registered) {
			clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

			/* make hub_wq clean up old urbs and devices */
			usb_set_device_state(hcd->self.root_hub,
					USB_STATE_NOTATTACHED);
			usb_kick_hub_wq(hcd->self.root_hub);
		}
	}

	/* Handle the case where this function gets called with a shared HCD */
	if (usb_hcd_is_primary_hcd(hcd))
		schedule_work(&hcd->died_work);
	else
		schedule_work(&hcd->primary_hcd->died_work);

	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
	/* Make sure that the other roothub is also deallocated. */
}
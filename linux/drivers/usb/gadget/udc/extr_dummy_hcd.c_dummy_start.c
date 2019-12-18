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
struct TYPE_3__ {int otg_port; } ;
struct usb_hcd {int uses_new_polling; TYPE_1__ self; int /*<<< orphan*/  state; int /*<<< orphan*/  power_budget; } ;
struct dummy_hcd {int /*<<< orphan*/  urbp_list; int /*<<< orphan*/  rh_state; int /*<<< orphan*/  timer; TYPE_2__* dum; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_RH_RUNNING ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POWER_BUDGET ; 
 int /*<<< orphan*/  dev_attr_urbs ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy_hcd*) ; 
 int dummy_start_ss (struct dummy_hcd*) ; 
 int /*<<< orphan*/  dummy_timer ; 
 struct dummy_hcd* hcd_to_dummy_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_is_primary_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int dummy_start(struct usb_hcd *hcd)
{
	struct dummy_hcd	*dum_hcd = hcd_to_dummy_hcd(hcd);

	/*
	 * MASTER side init ... we emulate a root hub that'll only ever
	 * talk to one device (the slave side).  Also appears in sysfs,
	 * just like more familiar pci-based HCDs.
	 */
	if (!usb_hcd_is_primary_hcd(hcd))
		return dummy_start_ss(dum_hcd);

	spin_lock_init(&dum_hcd->dum->lock);
	timer_setup(&dum_hcd->timer, dummy_timer, 0);
	dum_hcd->rh_state = DUMMY_RH_RUNNING;

	INIT_LIST_HEAD(&dum_hcd->urbp_list);

	hcd->power_budget = POWER_BUDGET;
	hcd->state = HC_STATE_RUNNING;
	hcd->uses_new_polling = 1;

#ifdef CONFIG_USB_OTG
	hcd->self.otg_port = 1;
#endif

	/* FIXME 'urbs' should be a per-device thing, maybe in usbcore */
	return device_create_file(dummy_dev(dum_hcd), &dev_attr_urbs);
}
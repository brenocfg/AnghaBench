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
struct usb_device {int dummy; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct usb_device* root_hub; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_may_wakeup (int /*<<< orphan*/ ) ; 
 TYPE_2__* dwc2_hsotg_to_hcd (struct dwc2_hsotg*) ; 
 scalar_t__ usb_wakeup_enabled_descendants (struct usb_device*) ; 

bool dwc2_host_can_poweroff_phy(struct dwc2_hsotg *dwc2)
{
	struct usb_device *root_hub = dwc2_hsotg_to_hcd(dwc2)->self.root_hub;

	/* If the controller isn't allowed to wakeup then we can power off. */
	if (!device_may_wakeup(dwc2->dev))
		return true;

	/*
	 * We don't want to power off the PHY if something under the
	 * root hub has wakeup enabled.
	 */
	if (usb_wakeup_enabled_descendants(root_hub))
		return false;

	/* No reason to keep the PHY powered, so allow poweroff */
	return true;
}
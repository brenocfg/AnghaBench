#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  speed; } ;
struct dwc2_hsotg {scalar_t__ lx_state; int num_of_eps; TYPE_5__** eps_out; TYPE_4__** eps_in; int /*<<< orphan*/  lock; TYPE_3__ gadget; scalar_t__ enabled; TYPE_2__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  ep; } ;
struct TYPE_9__ {int /*<<< orphan*/  ep; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ driver; } ;

/* Variables and functions */
 scalar_t__ DWC2_L0 ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_core_disconnect (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_disconnect (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_ep_disable_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dwc2_hsotg_suspend(struct dwc2_hsotg *hsotg)
{
	unsigned long flags;

	if (hsotg->lx_state != DWC2_L0)
		return 0;

	if (hsotg->driver) {
		int ep;

		dev_info(hsotg->dev, "suspending usb gadget %s\n",
			 hsotg->driver->driver.name);

		spin_lock_irqsave(&hsotg->lock, flags);
		if (hsotg->enabled)
			dwc2_hsotg_core_disconnect(hsotg);
		dwc2_hsotg_disconnect(hsotg);
		hsotg->gadget.speed = USB_SPEED_UNKNOWN;
		spin_unlock_irqrestore(&hsotg->lock, flags);

		for (ep = 0; ep < hsotg->num_of_eps; ep++) {
			if (hsotg->eps_in[ep])
				dwc2_hsotg_ep_disable_lock(&hsotg->eps_in[ep]->ep);
			if (hsotg->eps_out[ep])
				dwc2_hsotg_ep_disable_lock(&hsotg->eps_out[ep]->ep);
		}
	}

	return 0;
}
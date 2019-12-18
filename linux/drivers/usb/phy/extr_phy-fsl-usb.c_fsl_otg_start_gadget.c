#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {TYPE_2__* gadget; } ;
struct otg_fsm {struct usb_otg* otg; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_6__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* suspend ) (struct device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* resume ) (struct device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VDBG (char*,char*) ; 
 int /*<<< orphan*/  otg_suspend_state ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*,int /*<<< orphan*/ ) ; 

int fsl_otg_start_gadget(struct otg_fsm *fsm, int on)
{
	struct usb_otg *otg = fsm->otg;
	struct device *dev;

	if (!otg->gadget || !otg->gadget->dev.parent)
		return -ENODEV;

	VDBG("gadget %s\n", on ? "on" : "off");
	dev = otg->gadget->dev.parent;

	if (on) {
		if (dev->driver->resume)
			dev->driver->resume(dev);
	} else {
		if (dev->driver->suspend)
			dev->driver->suspend(dev, otg_suspend_state);
	}

	return 0;
}
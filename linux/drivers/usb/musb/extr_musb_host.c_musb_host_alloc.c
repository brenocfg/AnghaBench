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
struct musb {TYPE_2__* hcd; struct device* controller; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int uses_pio_for_control; } ;
struct TYPE_4__ {unsigned long* hcd_priv; int uses_new_polling; int has_tt; TYPE_1__ self; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  musb_hc_driver ; 
 TYPE_2__* usb_create_hcd (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ) ; 

int musb_host_alloc(struct musb *musb)
{
	struct device	*dev = musb->controller;

	/* usbcore sets dev->driver_data to hcd, and sometimes uses that... */
	musb->hcd = usb_create_hcd(&musb_hc_driver, dev, dev_name(dev));
	if (!musb->hcd)
		return -EINVAL;

	*musb->hcd->hcd_priv = (unsigned long) musb;
	musb->hcd->self.uses_pio_for_control = 1;
	musb->hcd->uses_new_polling = 1;
	musb->hcd->has_tt = 1;

	return 0;
}
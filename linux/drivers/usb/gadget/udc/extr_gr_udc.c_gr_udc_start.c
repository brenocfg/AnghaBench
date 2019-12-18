#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {TYPE_1__ driver; } ;
struct usb_gadget {int dummy; } ;
struct gr_udc {int /*<<< orphan*/  lock; struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  gr_enable_vbus_detect (struct gr_udc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct gr_udc* to_gr_udc (struct usb_gadget*) ; 

__attribute__((used)) static int gr_udc_start(struct usb_gadget *gadget,
			struct usb_gadget_driver *driver)
{
	struct gr_udc *dev = to_gr_udc(gadget);

	spin_lock(&dev->lock);

	/* Hook up the driver */
	driver->driver.bus = NULL;
	dev->driver = driver;

	/* Get ready for host detection */
	gr_enable_vbus_detect(dev);

	spin_unlock(&dev->lock);

	return 0;
}
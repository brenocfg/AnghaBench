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
struct usb_gadget_driver {int /*<<< orphan*/  max_speed; } ;
struct usb_gadget {int speed; } ;
struct dummy_hcd {struct dummy* dum; } ;
struct dummy {int ints_enabled; int /*<<< orphan*/  lock; struct usb_gadget_driver* driver; scalar_t__ devstatus; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy_hcd*) ; 
 struct dummy_hcd* gadget_to_dummy_hcd (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(g);
	struct dummy		*dum = dum_hcd->dum;

	switch (g->speed) {
	/* All the speeds we support */
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPER:
		break;
	default:
		dev_err(dummy_dev(dum_hcd), "Unsupported driver max speed %d\n",
				driver->max_speed);
		return -EINVAL;
	}

	/*
	 * SLAVE side init ... the layer above hardware, which
	 * can't enumerate without help from the driver we're binding.
	 */

	spin_lock_irq(&dum->lock);
	dum->devstatus = 0;
	dum->driver = driver;
	dum->ints_enabled = 1;
	spin_unlock_irq(&dum->lock);

	return 0;
}
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
struct usb_gadget_driver {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct pxa25x_udc {TYPE_1__ gadget; int /*<<< orphan*/  timer; struct pxa25x_ep* ep; } ;
struct pxa25x_ep {int stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int PXA_UDC_NUM_ENDPOINTS ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nuke (struct pxa25x_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_reinit (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  usb_gadget_udc_reset (TYPE_1__*,struct usb_gadget_driver*) ; 

__attribute__((used)) static void
reset_gadget(struct pxa25x_udc *dev, struct usb_gadget_driver *driver)
{
	int i;

	/* don't disconnect drivers more than once */
	if (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* prevent new request submissions, kill any outstanding requests  */
	for (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		struct pxa25x_ep *ep = &dev->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}
	del_timer_sync(&dev->timer);

	/* report reset; the driver is already quiesced */
	if (driver)
		usb_gadget_udc_reset(&dev->gadget, driver);

	/* re-init driver-visible data structures */
	udc_reinit(dev);
}
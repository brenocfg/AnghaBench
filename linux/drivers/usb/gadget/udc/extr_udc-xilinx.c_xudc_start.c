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
struct TYPE_4__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  name; } ;
struct xusb_udc {int /*<<< orphan*/  lock; scalar_t__ remote_wkp; int /*<<< orphan*/  addr; int /*<<< orphan*/  (* write_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__ gadget; struct usb_gadget_driver* driver; int /*<<< orphan*/  dev; struct xusb_ep* ep; } ;
struct xusb_ep {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct usb_gadget_driver {int /*<<< orphan*/  max_speed; TYPE_1__ driver; } ;
struct usb_gadget {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  XUSB_ADDRESS_OFFSET ; 
 size_t XUSB_EP_NUMBER_ZERO ; 
 int __xudc_ep_enable (struct xusb_ep*,struct usb_endpoint_descriptor const*) ; 
 struct usb_endpoint_descriptor config_bulk_out_desc ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xusb_udc* to_udc (struct usb_gadget*) ; 

__attribute__((used)) static int xudc_start(struct usb_gadget *gadget,
		      struct usb_gadget_driver *driver)
{
	struct xusb_udc *udc	= to_udc(gadget);
	struct xusb_ep *ep0	= &udc->ep[XUSB_EP_NUMBER_ZERO];
	const struct usb_endpoint_descriptor *desc = &config_bulk_out_desc;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&udc->lock, flags);

	if (udc->driver) {
		dev_err(udc->dev, "%s is already bound to %s\n",
			udc->gadget.name, udc->driver->driver.name);
		ret = -EBUSY;
		goto err;
	}

	/* hook up the driver */
	udc->driver = driver;
	udc->gadget.speed = driver->max_speed;

	/* Enable the control endpoint. */
	ret = __xudc_ep_enable(ep0, desc);

	/* Set device address and remote wakeup to 0 */
	udc->write_fn(udc->addr, XUSB_ADDRESS_OFFSET, 0);
	udc->remote_wkp = 0;
err:
	spin_unlock_irqrestore(&udc->lock, flags);
	return ret;
}
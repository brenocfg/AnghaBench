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
struct usb_gadget_driver {scalar_t__ max_speed; int /*<<< orphan*/  function; } ;
struct usb_gadget {int dummy; } ;
struct isp1760_udc {int connected; TYPE_1__* isp; int /*<<< orphan*/  gadget; scalar_t__ devstatus; int /*<<< orphan*/  lock; struct usb_gadget_driver* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_GLINTENA ; 
 int /*<<< orphan*/  DC_MODE ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_STATE_ATTACHED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct isp1760_udc* gadget_to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  isp1760_udc_init_hw (struct isp1760_udc*) ; 
 int /*<<< orphan*/  isp1760_udc_write (struct isp1760_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_gadget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp1760_udc_start(struct usb_gadget *gadget,
			     struct usb_gadget_driver *driver)
{
	struct isp1760_udc *udc = gadget_to_udc(gadget);
	unsigned long flags;

	/* The hardware doesn't support low speed. */
	if (driver->max_speed < USB_SPEED_FULL) {
		dev_err(udc->isp->dev, "Invalid gadget driver\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&udc->lock, flags);

	if (udc->driver) {
		dev_err(udc->isp->dev, "UDC already has a gadget driver\n");
		spin_unlock_irqrestore(&udc->lock, flags);
		return -EBUSY;
	}

	udc->driver = driver;

	spin_unlock_irqrestore(&udc->lock, flags);

	dev_dbg(udc->isp->dev, "starting UDC with driver %s\n",
		driver->function);

	udc->devstatus = 0;
	udc->connected = true;

	usb_gadget_set_state(&udc->gadget, USB_STATE_ATTACHED);

	/* DMA isn't supported yet, don't enable the DMA clock. */
	isp1760_udc_write(udc, DC_MODE, DC_GLINTENA);

	isp1760_udc_init_hw(udc);

	dev_dbg(udc->isp->dev, "UDC started with driver %s\n",
		driver->function);

	return 0;
}
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
struct usb_gadget_driver {int max_speed; } ;
struct usb_gadget {int /*<<< orphan*/  max_speed; } ;
struct cdns3_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* regs; struct usb_gadget_driver* gadget_driver; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_2__ {int /*<<< orphan*/  usb_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CONF_SFORCE_FS ; 
 int /*<<< orphan*/  USB_CONF_USB3DIS ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_UNKNOWN 128 
 int /*<<< orphan*/  cdns3_gadget_config (struct cdns3_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct cdns3_device* gadget_to_cdns3_device (struct usb_gadget*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_gadget_udc_start(struct usb_gadget *gadget,
				  struct usb_gadget_driver *driver)
{
	struct cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	unsigned long flags;
	enum usb_device_speed max_speed = driver->max_speed;

	spin_lock_irqsave(&priv_dev->lock, flags);
	priv_dev->gadget_driver = driver;

	/* limit speed if necessary */
	max_speed = min(driver->max_speed, gadget->max_speed);

	switch (max_speed) {
	case USB_SPEED_FULL:
		writel(USB_CONF_SFORCE_FS, &priv_dev->regs->usb_conf);
		writel(USB_CONF_USB3DIS, &priv_dev->regs->usb_conf);
		break;
	case USB_SPEED_HIGH:
		writel(USB_CONF_USB3DIS, &priv_dev->regs->usb_conf);
		break;
	case USB_SPEED_SUPER:
		break;
	default:
		dev_err(priv_dev->dev,
			"invalid maximum_speed parameter %d\n",
			max_speed);
		/* fall through */
	case USB_SPEED_UNKNOWN:
		/* default to superspeed */
		max_speed = USB_SPEED_SUPER;
		break;
	}

	cdns3_gadget_config(priv_dev);
	spin_unlock_irqrestore(&priv_dev->lock, flags);
	return 0;
}
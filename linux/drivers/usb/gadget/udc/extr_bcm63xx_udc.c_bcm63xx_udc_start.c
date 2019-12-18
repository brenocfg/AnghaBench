#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {scalar_t__ max_speed; TYPE_1__ driver; int /*<<< orphan*/  setup; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {TYPE_2__ dev; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; TYPE_4__* dev; TYPE_3__ gadget; struct usb_gadget_driver* driver; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  bcm63xx_ep_init (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_ep_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_fifo_reset (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_fifo_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_select_phy_mode (struct bcm63xx_udc*,int) ; 
 struct bcm63xx_udc* gadget_to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  set_clocks (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm63xx_udc_start(struct usb_gadget *gadget,
		struct usb_gadget_driver *driver)
{
	struct bcm63xx_udc *udc = gadget_to_udc(gadget);
	unsigned long flags;

	if (!driver || driver->max_speed < USB_SPEED_HIGH ||
	    !driver->setup)
		return -EINVAL;
	if (!udc)
		return -ENODEV;
	if (udc->driver)
		return -EBUSY;

	spin_lock_irqsave(&udc->lock, flags);

	set_clocks(udc, true);
	bcm63xx_fifo_setup(udc);
	bcm63xx_ep_init(udc);
	bcm63xx_ep_setup(udc);
	bcm63xx_fifo_reset(udc);
	bcm63xx_select_phy_mode(udc, true);

	udc->driver = driver;
	driver->driver.bus = NULL;
	udc->gadget.dev.of_node = udc->dev->of_node;

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}
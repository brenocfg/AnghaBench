#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ speed; } ;
struct bcm63xx_udc {int ep0_req_reset; int ep0_req_set_cfg; int ep0_req_set_iface; TYPE_2__* driver; TYPE_1__ gadget; int /*<<< orphan*/  lock; int /*<<< orphan*/  ep0_wq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* disconnect ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USBD_EVENTS_REG ; 
 int USBD_EVENTS_USB_LINK_MASK ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_MASK_REG ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_SETCFG ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_SETINTF ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_SETUP ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_STATUS_REG ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_USB_LINK ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_USB_RESET ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  bcm63xx_ep_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_fifo_reset (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_fifo_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_update_cfg_iface (struct bcm63xx_udc*) ; 
 scalar_t__ bcm63xx_update_link_speed (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_update_wedge (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_gadget_udc_reset (TYPE_1__*,TYPE_2__*) ; 
 int usbd_readl (struct bcm63xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_writel (struct bcm63xx_udc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm63xx_udc_ctrl_isr(int irq, void *dev_id)
{
	struct bcm63xx_udc *udc = dev_id;
	u32 stat;
	bool disconnected = false, bus_reset = false;

	stat = usbd_readl(udc, USBD_EVENT_IRQ_STATUS_REG) &
	       usbd_readl(udc, USBD_EVENT_IRQ_MASK_REG);

	usbd_writel(udc, stat, USBD_EVENT_IRQ_STATUS_REG);

	spin_lock(&udc->lock);
	if (stat & BIT(USBD_EVENT_IRQ_USB_LINK)) {
		/* VBUS toggled */

		if (!(usbd_readl(udc, USBD_EVENTS_REG) &
		      USBD_EVENTS_USB_LINK_MASK) &&
		      udc->gadget.speed != USB_SPEED_UNKNOWN)
			dev_info(udc->dev, "link down\n");

		udc->gadget.speed = USB_SPEED_UNKNOWN;
		disconnected = true;
	}
	if (stat & BIT(USBD_EVENT_IRQ_USB_RESET)) {
		bcm63xx_fifo_setup(udc);
		bcm63xx_fifo_reset(udc);
		bcm63xx_ep_setup(udc);

		bcm63xx_update_wedge(udc, false);

		udc->ep0_req_reset = 1;
		schedule_work(&udc->ep0_wq);
		bus_reset = true;
	}
	if (stat & BIT(USBD_EVENT_IRQ_SETUP)) {
		if (bcm63xx_update_link_speed(udc)) {
			bcm63xx_fifo_setup(udc);
			bcm63xx_ep_setup(udc);
		}
		bcm63xx_update_wedge(udc, true);
	}
	if (stat & BIT(USBD_EVENT_IRQ_SETCFG)) {
		bcm63xx_update_cfg_iface(udc);
		udc->ep0_req_set_cfg = 1;
		schedule_work(&udc->ep0_wq);
	}
	if (stat & BIT(USBD_EVENT_IRQ_SETINTF)) {
		bcm63xx_update_cfg_iface(udc);
		udc->ep0_req_set_iface = 1;
		schedule_work(&udc->ep0_wq);
	}
	spin_unlock(&udc->lock);

	if (disconnected && udc->driver)
		udc->driver->disconnect(&udc->gadget);
	else if (bus_reset && udc->driver)
		usb_gadget_udc_reset(&udc->gadget, udc->driver);

	return IRQ_HANDLED;
}
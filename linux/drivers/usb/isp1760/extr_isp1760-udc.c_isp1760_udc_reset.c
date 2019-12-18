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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct isp1760_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  driver; TYPE_1__ gadget; int /*<<< orphan*/  ep0_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1760_CTRL_SETUP ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  isp1760_udc_init_hw (struct isp1760_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_gadget_udc_reset (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp1760_udc_reset(struct isp1760_udc *udc)
{
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * The bus reset has reset most registers to their default value,
	 * reinitialize the UDC hardware.
	 */
	isp1760_udc_init_hw(udc);

	udc->ep0_state = ISP1760_CTRL_SETUP;
	udc->gadget.speed = USB_SPEED_FULL;

	usb_gadget_udc_reset(&udc->gadget, udc->driver);

	spin_unlock_irqrestore(&udc->lock, flags);
}
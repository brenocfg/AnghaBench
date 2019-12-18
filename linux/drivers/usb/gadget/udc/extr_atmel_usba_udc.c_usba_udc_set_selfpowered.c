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
struct usba_udc {int devstatus; int /*<<< orphan*/  lock; } ;
struct usb_gadget {int is_selfpowered; } ;

/* Variables and functions */
 int USB_DEVICE_SELF_POWERED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usba_udc* to_usba_udc (struct usb_gadget*) ; 

__attribute__((used)) static int
usba_udc_set_selfpowered(struct usb_gadget *gadget, int is_selfpowered)
{
	struct usba_udc *udc = to_usba_udc(gadget);
	unsigned long flags;

	gadget->is_selfpowered = (is_selfpowered != 0);
	spin_lock_irqsave(&udc->lock, flags);
	if (is_selfpowered)
		udc->devstatus |= 1 << USB_DEVICE_SELF_POWERED;
	else
		udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}
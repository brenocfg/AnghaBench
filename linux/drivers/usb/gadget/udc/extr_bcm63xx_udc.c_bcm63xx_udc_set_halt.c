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
struct usb_ep {int dummy; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; } ;
struct bcm63xx_ep {int halted; struct bcm63xx_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm63xx_set_stall (struct bcm63xx_udc*,struct bcm63xx_ep*,int) ; 
 struct bcm63xx_ep* our_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm63xx_udc_set_halt(struct usb_ep *ep, int value)
{
	struct bcm63xx_ep *bep = our_ep(ep);
	struct bcm63xx_udc *udc = bep->udc;
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);
	bcm63xx_set_stall(udc, bep, !!value);
	bep->halted = value;
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}
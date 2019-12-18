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
struct usb_gadget {int dummy; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm63xx_select_phy_mode (struct bcm63xx_udc*,int) ; 
 struct bcm63xx_udc* gadget_to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_clocks (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm63xx_udc_stop(struct usb_gadget *gadget)
{
	struct bcm63xx_udc *udc = gadget_to_udc(gadget);
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	udc->driver = NULL;

	/*
	 * If we switch the PHY too abruptly after dropping D+, the host
	 * will often complain:
	 *
	 *     hub 1-0:1.0: port 1 disabled by hub (EMI?), re-enabling...
	 */
	msleep(100);

	bcm63xx_select_phy_mode(udc, false);
	set_clocks(udc, false);

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}
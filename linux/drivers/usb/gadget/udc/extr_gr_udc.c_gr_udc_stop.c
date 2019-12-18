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
struct gr_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  gr_stop_activity (struct gr_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gr_udc* to_gr_udc (struct usb_gadget*) ; 

__attribute__((used)) static int gr_udc_stop(struct usb_gadget *gadget)
{
	struct gr_udc *dev = to_gr_udc(gadget);
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);

	dev->driver = NULL;
	gr_stop_activity(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}
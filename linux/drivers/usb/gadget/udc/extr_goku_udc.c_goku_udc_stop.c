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
struct goku_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_activity (struct goku_udc*) ; 
 struct goku_udc* to_goku_udc (struct usb_gadget*) ; 

__attribute__((used)) static int goku_udc_stop(struct usb_gadget *g)
{
	struct goku_udc	*dev = to_goku_udc(g);
	unsigned long	flags;

	spin_lock_irqsave(&dev->lock, flags);
	dev->driver = NULL;
	stop_activity(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}
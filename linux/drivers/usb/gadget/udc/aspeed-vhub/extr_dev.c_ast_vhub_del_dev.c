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
struct ast_vhub_dev {int registered; int /*<<< orphan*/  port_dev; int /*<<< orphan*/  gadget; TYPE_1__* vhub; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

void ast_vhub_del_dev(struct ast_vhub_dev *d)
{
	unsigned long flags;

	spin_lock_irqsave(&d->vhub->lock, flags);
	if (!d->registered) {
		spin_unlock_irqrestore(&d->vhub->lock, flags);
		return;
	}
	d->registered = false;
	spin_unlock_irqrestore(&d->vhub->lock, flags);

	usb_del_gadget_udc(&d->gadget);
	device_unregister(d->port_dev);
}
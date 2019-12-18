#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget_driver {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_3__ {int is_selfpowered; } ;
struct ast_vhub_dev {TYPE_2__* vhub; TYPE_1__ gadget; struct usb_gadget_driver* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ast_vhub_dev* to_ast_dev (struct usb_gadget*) ; 

__attribute__((used)) static int ast_vhub_udc_start(struct usb_gadget *gadget,
			      struct usb_gadget_driver *driver)
{
	struct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned long flags;

	spin_lock_irqsave(&d->vhub->lock, flags);

	DDBG(d, "start\n");

	/* We don't do much more until the hub enables us */
	d->driver = driver;
	d->gadget.is_selfpowered = 1;

	spin_unlock_irqrestore(&d->vhub->lock, flags);

	return 0;
}
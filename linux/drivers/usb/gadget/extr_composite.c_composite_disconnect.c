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
struct usb_gadget {int dummy; } ;
struct usb_composite_dev {int /*<<< orphan*/  lock; TYPE_1__* driver; scalar_t__ config; scalar_t__ suspended; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (struct usb_composite_dev*) ;} ;

/* Variables and functions */
 struct usb_composite_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  reset_config (struct usb_composite_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct usb_composite_dev*) ; 

void composite_disconnect(struct usb_gadget *gadget)
{
	struct usb_composite_dev	*cdev = get_gadget_data(gadget);
	unsigned long			flags;

	/* REVISIT:  should we have config and device level
	 * disconnect callbacks?
	 */
	spin_lock_irqsave(&cdev->lock, flags);
	cdev->suspended = 0;
	if (cdev->config)
		reset_config(cdev);
	if (cdev->driver->disconnect)
		cdev->driver->disconnect(cdev);
	spin_unlock_irqrestore(&cdev->lock, flags);
}
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
struct usb_ctrlrequest {int dummy; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 

__attribute__((used)) static int bcm63xx_ep0_setup_callback(struct bcm63xx_udc *udc,
	struct usb_ctrlrequest *ctrl)
{
	int rc;

	spin_unlock_irq(&udc->lock);
	rc = udc->driver->setup(&udc->gadget, ctrl);
	spin_lock_irq(&udc->lock);
	return rc;
}
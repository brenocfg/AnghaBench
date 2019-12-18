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
struct usb_hub {int /*<<< orphan*/  irq_urb_lock; int /*<<< orphan*/  irq_urb_retry; int /*<<< orphan*/  intfdev; int /*<<< orphan*/  urb; scalar_t__ quiescing; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hub_resubmit_irq_urb(struct usb_hub *hub)
{
	unsigned long flags;
	int status;

	spin_lock_irqsave(&hub->irq_urb_lock, flags);

	if (hub->quiescing) {
		spin_unlock_irqrestore(&hub->irq_urb_lock, flags);
		return;
	}

	status = usb_submit_urb(hub->urb, GFP_ATOMIC);
	if (status && status != -ENODEV && status != -EPERM &&
	    status != -ESHUTDOWN) {
		dev_err(hub->intfdev, "resubmit --> %d\n", status);
		mod_timer(&hub->irq_urb_retry, jiffies + HZ);
	}

	spin_unlock_irqrestore(&hub->irq_urb_lock, flags);
}
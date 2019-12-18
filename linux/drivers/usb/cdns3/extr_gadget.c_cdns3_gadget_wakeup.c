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
struct cdns3_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __cdns3_gadget_wakeup (struct cdns3_device*) ; 
 struct cdns3_device* gadget_to_cdns3_device (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cdns3_gadget_wakeup(struct usb_gadget *gadget)
{
	struct cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&priv_dev->lock, flags);
	ret = __cdns3_gadget_wakeup(priv_dev);
	spin_unlock_irqrestore(&priv_dev->lock, flags);
	return ret;
}
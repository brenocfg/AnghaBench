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
typedef  int u32 ;
struct usba_udc {int devstatus; int /*<<< orphan*/  lock; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int EINVAL ; 
 int USBA_REMOTE_WAKE_UP ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usba_udc* to_usba_udc (struct usb_gadget*) ; 
 int usba_readl (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usba_udc_wakeup(struct usb_gadget *gadget)
{
	struct usba_udc *udc = to_usba_udc(gadget);
	unsigned long flags;
	u32 ctrl;
	int ret = -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	if (udc->devstatus & (1 << USB_DEVICE_REMOTE_WAKEUP)) {
		ctrl = usba_readl(udc, CTRL);
		usba_writel(udc, CTRL, ctrl | USBA_REMOTE_WAKE_UP);
		ret = 0;
	}
	spin_unlock_irqrestore(&udc->lock, flags);

	return ret;
}
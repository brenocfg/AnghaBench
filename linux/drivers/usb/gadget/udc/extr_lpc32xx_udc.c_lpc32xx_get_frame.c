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
struct lpc32xx_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  clocked; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct lpc32xx_udc* to_udc (struct usb_gadget*) ; 
 scalar_t__ udc_get_current_frame (struct lpc32xx_udc*) ; 

__attribute__((used)) static int lpc32xx_get_frame(struct usb_gadget *gadget)
{
	int frame;
	unsigned long flags;
	struct lpc32xx_udc *udc = to_udc(gadget);

	if (!udc->clocked)
		return -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);

	frame = (int) udc_get_current_frame(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	return frame;
}
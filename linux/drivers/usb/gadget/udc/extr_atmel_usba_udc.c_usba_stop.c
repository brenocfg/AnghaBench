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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct usba_udc {int /*<<< orphan*/  lock; TYPE_1__ gadget; scalar_t__ suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  USBA_DISABLE_MASK ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  reset_all_endpoints (struct usba_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_clock (struct usba_udc*) ; 
 int /*<<< orphan*/  toggle_bias (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usba_stop(struct usba_udc *udc)
{
	unsigned long flags;

	if (udc->suspended)
		return;

	spin_lock_irqsave(&udc->lock, flags);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	reset_all_endpoints(udc);

	/* This will also disable the DP pullup */
	toggle_bias(udc, 0);
	usba_writel(udc, CTRL, USBA_DISABLE_MASK);
	spin_unlock_irqrestore(&udc->lock, flags);

	stop_clock(udc);
}
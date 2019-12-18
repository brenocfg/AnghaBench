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
struct usba_udc {int /*<<< orphan*/  lock; scalar_t__ int_enb_cache; scalar_t__ suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  INT_CLR ; 
 int /*<<< orphan*/  INT_ENB ; 
 int USBA_DET_SUSPEND ; 
 int USBA_ENABLE_MASK ; 
 int USBA_END_OF_RESET ; 
 int USBA_END_OF_RESUME ; 
 int USBA_WAKE_UP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int start_clock (struct usba_udc*) ; 
 int /*<<< orphan*/  toggle_bias (struct usba_udc*,int) ; 
 int /*<<< orphan*/  usba_int_enb_set (struct usba_udc*,int) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usba_start(struct usba_udc *udc)
{
	unsigned long flags;
	int ret;

	ret = start_clock(udc);
	if (ret)
		return ret;

	if (udc->suspended)
		return 0;

	spin_lock_irqsave(&udc->lock, flags);
	toggle_bias(udc, 1);
	usba_writel(udc, CTRL, USBA_ENABLE_MASK);
	/* Clear all requested and pending interrupts... */
	usba_writel(udc, INT_ENB, 0);
	udc->int_enb_cache = 0;
	usba_writel(udc, INT_CLR,
		USBA_END_OF_RESET|USBA_END_OF_RESUME
		|USBA_DET_SUSPEND|USBA_WAKE_UP);
	/* ...and enable just 'reset' IRQ to get us started */
	usba_int_enb_set(udc, USBA_END_OF_RESET);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}
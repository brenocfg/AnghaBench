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
struct xenfb_page {scalar_t__ in_cons; scalar_t__ in_prod; } ;
struct xenfb_info {int /*<<< orphan*/  irq; struct xenfb_page* page; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenfb_refresh (struct xenfb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t xenfb_event_handler(int rq, void *dev_id)
{
	/*
	 * No in events recognized, simply ignore them all.
	 * If you need to recognize some, see xen-kbdfront's
	 * input_handler() for how to do that.
	 */
	struct xenfb_info *info = dev_id;
	struct xenfb_page *page = info->page;

	if (page->in_cons != page->in_prod) {
		info->page->in_cons = info->page->in_prod;
		notify_remote_via_irq(info->irq);
	}

	/* Flush dirty rectangle: */
	xenfb_refresh(info, INT_MAX, INT_MAX, -INT_MAX, -INT_MAX);

	return IRQ_HANDLED;
}
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
struct dwc3 {int /*<<< orphan*/  ev_buf; int /*<<< orphan*/  irq_gadget; int /*<<< orphan*/  lock; int /*<<< orphan*/ * gadget_driver; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dwc3_gadget_stop (struct dwc3*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dwc3* gadget_to_dwc (struct usb_gadget*) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc3_gadget_stop(struct usb_gadget *g)
{
	struct dwc3		*dwc = gadget_to_dwc(g);
	unsigned long		flags;

	spin_lock_irqsave(&dwc->lock, flags);

	if (pm_runtime_suspended(dwc->dev))
		goto out;

	__dwc3_gadget_stop(dwc);

out:
	dwc->gadget_driver	= NULL;
	spin_unlock_irqrestore(&dwc->lock, flags);

	free_irq(dwc->irq_gadget, dwc->ev_buf);

	return 0;
}
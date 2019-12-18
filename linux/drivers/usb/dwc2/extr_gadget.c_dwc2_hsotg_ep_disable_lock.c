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
struct usb_ep {int dummy; } ;
struct dwc2_hsotg_ep {struct dwc2_hsotg* parent; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int dwc2_hsotg_ep_disable (struct usb_ep*) ; 
 struct dwc2_hsotg_ep* our_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc2_hsotg_ep_disable_lock(struct usb_ep *ep)
{
	struct dwc2_hsotg_ep *hs_ep = our_ep(ep);
	struct dwc2_hsotg *hsotg = hs_ep->parent;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&hsotg->lock, flags);
	ret = dwc2_hsotg_ep_disable(ep);
	spin_unlock_irqrestore(&hsotg->lock, flags);
	return ret;
}
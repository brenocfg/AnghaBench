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
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;
struct dwc2_hsotg_ep {struct dwc2_hsotg* parent; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int dwc2_hsotg_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 
 struct dwc2_hsotg_ep* our_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc2_hsotg_ep_queue_lock(struct usb_ep *ep, struct usb_request *req,
				    gfp_t gfp_flags)
{
	struct dwc2_hsotg_ep *hs_ep = our_ep(ep);
	struct dwc2_hsotg *hs = hs_ep->parent;
	unsigned long flags = 0;
	int ret = 0;

	spin_lock_irqsave(&hs->lock, flags);
	ret = dwc2_hsotg_ep_queue(ep, req, gfp_flags);
	spin_unlock_irqrestore(&hs->lock, flags);

	return ret;
}
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
struct usb_host_endpoint {struct max3421_ep* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct max3421_hcd {int /*<<< orphan*/  lock; } ;
struct max3421_ep {int /*<<< orphan*/  ep_list; } ;

/* Variables and functions */
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  kfree (struct max3421_ep*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
max3421_endpoint_disable(struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned long flags;

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	if (ep->hcpriv) {
		struct max3421_ep *max3421_ep = ep->hcpriv;

		/* remove myself from the ep_list: */
		if (!list_empty(&max3421_ep->ep_list))
			list_del(&max3421_ep->ep_list);
		kfree(max3421_ep);
		ep->hcpriv = NULL;
	}

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
}
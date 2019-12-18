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
struct usb_ep {TYPE_1__* desc; } ;
struct cdns3_endpoint {int flags; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int EPERM ; 
 int EP_ENABLED ; 
 int EP_WEDGE ; 
 int __cdns3_gadget_ep_clear_halt (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  __cdns3_gadget_ep_set_halt (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int /*<<< orphan*/ ) ; 
 struct cdns3_endpoint* ep_to_cdns3_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cdns3_gadget_ep_set_halt(struct usb_ep *ep, int value)
{
	struct cdns3_endpoint *priv_ep = ep_to_cdns3_ep(ep);
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	unsigned long flags;
	int ret = 0;

	if (!(priv_ep->flags & EP_ENABLED))
		return -EPERM;

	spin_lock_irqsave(&priv_dev->lock, flags);

	cdns3_select_ep(priv_dev, ep->desc->bEndpointAddress);

	if (!value) {
		priv_ep->flags &= ~EP_WEDGE;
		ret = __cdns3_gadget_ep_clear_halt(priv_ep);
	} else {
		__cdns3_gadget_ep_set_halt(priv_ep);
	}

	spin_unlock_irqrestore(&priv_dev->lock, flags);

	return ret;
}
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
struct usb_request {int length; int /*<<< orphan*/  buf; scalar_t__ zero; } ;
struct usb_ep {int maxpacket; } ;
struct cdns3_request {int /*<<< orphan*/  flags; } ;
struct cdns3_endpoint {int /*<<< orphan*/  name; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  zlp_buf; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REQUEST_ZLP ; 
 int __cdns3_gadget_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 
 struct usb_request* cdns3_gadget_ep_alloc_request (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cdns3_endpoint* ep_to_cdns3_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cdns3_request* to_cdns3_request (struct usb_request*) ; 

__attribute__((used)) static int cdns3_gadget_ep_queue(struct usb_ep *ep, struct usb_request *request,
				 gfp_t gfp_flags)
{
	struct usb_request *zlp_request;
	struct cdns3_endpoint *priv_ep;
	struct cdns3_device *priv_dev;
	unsigned long flags;
	int ret;

	if (!request || !ep)
		return -EINVAL;

	priv_ep = ep_to_cdns3_ep(ep);
	priv_dev = priv_ep->cdns3_dev;

	spin_lock_irqsave(&priv_dev->lock, flags);

	ret = __cdns3_gadget_ep_queue(ep, request, gfp_flags);

	if (ret == 0 && request->zero && request->length &&
	    (request->length % ep->maxpacket == 0)) {
		struct cdns3_request *priv_req;

		zlp_request = cdns3_gadget_ep_alloc_request(ep, GFP_ATOMIC);
		zlp_request->buf = priv_dev->zlp_buf;
		zlp_request->length = 0;

		priv_req = to_cdns3_request(zlp_request);
		priv_req->flags |= REQUEST_ZLP;

		dev_dbg(priv_dev->dev, "Queuing ZLP for endpoint: %s\n",
			priv_ep->name);
		ret = __cdns3_gadget_ep_queue(ep, zlp_request, gfp_flags);
	}

	spin_unlock_irqrestore(&priv_dev->lock, flags);
	return ret;
}
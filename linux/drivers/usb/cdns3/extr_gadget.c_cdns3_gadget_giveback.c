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
struct usb_request {int status; scalar_t__ buf; scalar_t__ complete; int /*<<< orphan*/  length; int /*<<< orphan*/  list; } ;
struct cdns3_request {int flags; TYPE_1__* aligned_buf; struct usb_request request; } ;
struct cdns3_endpoint {int /*<<< orphan*/  endpoint; int /*<<< orphan*/  dir; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {scalar_t__ dev_ver; scalar_t__ zlp_buf; int /*<<< orphan*/  lock; int /*<<< orphan*/  sysdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ DEV_VER_V2 ; 
 int EINPROGRESS ; 
 int REQUEST_PENDING ; 
 int REQUEST_UNALIGNED ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  cdns3_gadget_ep_free_request (int /*<<< orphan*/ *,struct usb_request*) ; 
 struct usb_request* cdns3_wa2_gadget_giveback (struct cdns3_device*,struct cdns3_endpoint*,struct cdns3_request*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_gadget_giveback (struct cdns3_request*) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (int /*<<< orphan*/ *,struct usb_request*) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request_by_dev (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

void cdns3_gadget_giveback(struct cdns3_endpoint *priv_ep,
			   struct cdns3_request *priv_req,
			   int status)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	struct usb_request *request = &priv_req->request;

	list_del_init(&request->list);

	if (request->status == -EINPROGRESS)
		request->status = status;

	usb_gadget_unmap_request_by_dev(priv_dev->sysdev, request,
					priv_ep->dir);

	if ((priv_req->flags & REQUEST_UNALIGNED) &&
	    priv_ep->dir == USB_DIR_OUT && !request->status)
		memcpy(request->buf, priv_req->aligned_buf->buf,
		       request->length);

	priv_req->flags &= ~(REQUEST_PENDING | REQUEST_UNALIGNED);
	trace_cdns3_gadget_giveback(priv_req);

	if (priv_dev->dev_ver < DEV_VER_V2) {
		request = cdns3_wa2_gadget_giveback(priv_dev, priv_ep,
						    priv_req);
		if (!request)
			return;
	}

	if (request->complete) {
		spin_unlock(&priv_dev->lock);
		usb_gadget_giveback_request(&priv_ep->endpoint,
					    request);
		spin_lock(&priv_dev->lock);
	}

	if (request->buf == priv_dev->zlp_buf)
		cdns3_gadget_ep_free_request(&priv_ep->endpoint, request);
}
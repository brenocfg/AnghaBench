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
struct usb_request {scalar_t__ length; scalar_t__ actual; int /*<<< orphan*/  list; int /*<<< orphan*/  status; } ;
struct cdns3_request {int flags; struct usb_request request; } ;
struct cdns3_endpoint {int flags; int /*<<< orphan*/ * descmis_req; int /*<<< orphan*/  deferred_req_list; } ;
struct cdns3_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int EP_QUIRK_END_TRANSFER ; 
 int EP_QUIRK_EXTRA_BUF_EN ; 
 int REQUEST_INTERNAL ; 
 struct usb_request* cdns3_next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdns3_start_all_request (struct cdns3_device*,struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  cdns3_wa2_descmiss_copy_data (struct cdns3_endpoint*,struct usb_request*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

struct usb_request *cdns3_wa2_gadget_giveback(struct cdns3_device *priv_dev,
					      struct cdns3_endpoint *priv_ep,
					      struct cdns3_request *priv_req)
{
	if (priv_ep->flags & EP_QUIRK_EXTRA_BUF_EN &&
	    priv_req->flags & REQUEST_INTERNAL) {
		struct usb_request *req;

		req = cdns3_next_request(&priv_ep->deferred_req_list);

		priv_ep->descmis_req = NULL;

		if (!req)
			return NULL;

		cdns3_wa2_descmiss_copy_data(priv_ep, req);
		if (!(priv_ep->flags & EP_QUIRK_END_TRANSFER) &&
		    req->length != req->actual) {
			/* wait for next part of transfer */
			return NULL;
		}

		if (req->status == -EINPROGRESS)
			req->status = 0;

		list_del_init(&req->list);
		cdns3_start_all_request(priv_dev, priv_ep);
		return req;
	}

	return &priv_req->request;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_request {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  buf; } ;
struct cdns3_request {TYPE_2__ request; int /*<<< orphan*/  flags; } ;
struct cdns3_endpoint {int flags; scalar_t__ wa2_counter; TYPE_1__* cdns3_dev; struct cdns3_request* descmis_req; int /*<<< orphan*/  endpoint; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS3_DESCMIS_BUF_SIZE ; 
 scalar_t__ CDNS3_WA2_NUM_BUFFERS ; 
 int EP_QUIRK_EXTRA_BUF_DET ; 
 int EP_QUIRK_EXTRA_BUF_EN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REQUEST_INTERNAL ; 
 int /*<<< orphan*/  REQUEST_INTERNAL_CH ; 
 int /*<<< orphan*/  __cdns3_gadget_ep_queue (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct usb_request* cdns3_gadget_ep_alloc_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_gadget_ep_free_request (int /*<<< orphan*/ *,struct usb_request*) ; 
 int /*<<< orphan*/  cdns3_wa2_remove_old_request (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdns3_request* to_cdns3_request (struct usb_request*) ; 
 int /*<<< orphan*/  trace_cdns3_wa2 (struct cdns3_endpoint*,char*) ; 

__attribute__((used)) static void cdns3_wa2_descmissing_packet(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_request *priv_req;
	struct usb_request *request;

	if (priv_ep->flags & EP_QUIRK_EXTRA_BUF_DET) {
		priv_ep->flags &= ~EP_QUIRK_EXTRA_BUF_DET;
		priv_ep->flags |= EP_QUIRK_EXTRA_BUF_EN;
	}

	trace_cdns3_wa2(priv_ep, "Description Missing detected\n");

	if (priv_ep->wa2_counter >= CDNS3_WA2_NUM_BUFFERS)
		cdns3_wa2_remove_old_request(priv_ep);

	request = cdns3_gadget_ep_alloc_request(&priv_ep->endpoint,
						GFP_ATOMIC);
	if (!request)
		goto err;

	priv_req = to_cdns3_request(request);
	priv_req->flags |= REQUEST_INTERNAL;

	/* if this field is still assigned it indicate that transfer related
	 * with this request has not been finished yet. Driver in this
	 * case simply allocate next request and assign flag REQUEST_INTERNAL_CH
	 * flag to previous one. It will indicate that current request is
	 * part of the previous one.
	 */
	if (priv_ep->descmis_req)
		priv_ep->descmis_req->flags |= REQUEST_INTERNAL_CH;

	priv_req->request.buf = kzalloc(CDNS3_DESCMIS_BUF_SIZE,
					GFP_ATOMIC);
	priv_ep->wa2_counter++;

	if (!priv_req->request.buf) {
		cdns3_gadget_ep_free_request(&priv_ep->endpoint, request);
		goto err;
	}

	priv_req->request.length = CDNS3_DESCMIS_BUF_SIZE;
	priv_ep->descmis_req = priv_req;

	__cdns3_gadget_ep_queue(&priv_ep->endpoint,
				&priv_ep->descmis_req->request,
				GFP_ATOMIC);

	return;

err:
	dev_err(priv_ep->cdns3_dev->dev,
		"Failed: No sufficient memory for DESCMIS\n");
}
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
struct usb_request {int /*<<< orphan*/  actual; } ;
struct cdns3_endpoint {int /*<<< orphan*/  dir; TYPE_1__* trb_pool; int /*<<< orphan*/  pending_req_list; } ;
struct cdns3_device {int /*<<< orphan*/  ep0_data_dir; struct cdns3_endpoint** eps; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRB_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_ep0_complete_setup (struct cdns3_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_gadget_giveback (struct cdns3_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_request* cdns3_next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_cdns3_request (struct usb_request*) ; 
 int /*<<< orphan*/  trace_cdns3_complete_trb (struct cdns3_endpoint*,TYPE_1__*) ; 

__attribute__((used)) static void cdns3_transfer_completed(struct cdns3_device *priv_dev)
{
	struct cdns3_endpoint *priv_ep = priv_dev->eps[0];

	if (!list_empty(&priv_ep->pending_req_list)) {
		struct usb_request *request;

		trace_cdns3_complete_trb(priv_ep, priv_ep->trb_pool);
		request = cdns3_next_request(&priv_ep->pending_req_list);

		request->actual =
			TRB_LEN(le32_to_cpu(priv_ep->trb_pool->length));

		priv_ep->dir = priv_dev->ep0_data_dir;
		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request), 0);
	}

	cdns3_ep0_complete_setup(priv_dev, 0, 0);
}
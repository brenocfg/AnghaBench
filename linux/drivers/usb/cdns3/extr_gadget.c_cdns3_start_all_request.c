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
struct usb_request {int /*<<< orphan*/  list; } ;
struct cdns3_endpoint {int /*<<< orphan*/  flags; int /*<<< orphan*/  pending_req_list; int /*<<< orphan*/  deferred_req_list; } ;
struct cdns3_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_RING_FULL ; 
 int cdns3_ep_run_transfer (struct cdns3_endpoint*,struct usb_request*) ; 
 struct usb_request* cdns3_next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_start_all_request(struct cdns3_device *priv_dev,
				   struct cdns3_endpoint *priv_ep)
{
	struct usb_request *request;
	int ret = 0;

	while (!list_empty(&priv_ep->deferred_req_list)) {
		request = cdns3_next_request(&priv_ep->deferred_req_list);

		ret = cdns3_ep_run_transfer(priv_ep, request);
		if (ret)
			return ret;

		list_del(&request->list);
		list_add_tail(&request->list,
			      &priv_ep->pending_req_list);
	}

	priv_ep->flags &= ~EP_RING_FULL;
	return ret;
}
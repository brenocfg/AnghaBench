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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct cdns3_request {int flags; int /*<<< orphan*/  list; TYPE_1__ request; } ;
struct cdns3_endpoint {int /*<<< orphan*/  wa2_counter; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  wa2_descmiss_req_list; } ;

/* Variables and functions */
 int REQUEST_INTERNAL_CH ; 
 int /*<<< orphan*/  cdns3_gadget_ep_free_request (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct cdns3_request* cdns3_next_priv_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_wa2 (struct cdns3_endpoint*,char*) ; 

__attribute__((used)) static void cdns3_wa2_remove_old_request(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_request *priv_req;

	while (!list_empty(&priv_ep->wa2_descmiss_req_list)) {
		u8 chain;

		priv_req = cdns3_next_priv_request(&priv_ep->wa2_descmiss_req_list);
		chain = !!(priv_req->flags & REQUEST_INTERNAL_CH);

		trace_cdns3_wa2(priv_ep, "removes eldest request");

		kfree(priv_req->request.buf);
		cdns3_gadget_ep_free_request(&priv_ep->endpoint,
					     &priv_req->request);
		list_del_init(&priv_req->list);
		--priv_ep->wa2_counter;

		if (!chain)
			break;
	}
}
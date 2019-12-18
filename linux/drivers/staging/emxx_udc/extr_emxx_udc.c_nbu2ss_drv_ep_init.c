#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ep_list; TYPE_2__* ep0; } ;
struct nbu2ss_udc {struct nbu2ss_ep* ep; TYPE_1__ gadget; } ;
struct TYPE_5__ {int /*<<< orphan*/  ep_list; int /*<<< orphan*/ * ops; int /*<<< orphan*/  caps; int /*<<< orphan*/  name; int /*<<< orphan*/ * driver_data; } ;
struct nbu2ss_ep {TYPE_2__ ep; int /*<<< orphan*/  queue; int /*<<< orphan*/ * desc; struct nbu2ss_udc* udc; } ;
struct TYPE_6__ {int /*<<< orphan*/  caps; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP0_PACKETSIZE ; 
 int /*<<< orphan*/  EP_PACKETSIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_ENDPOINTS ; 
 TYPE_3__* ep_info ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbu2ss_ep_ops ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbu2ss_drv_ep_init(struct nbu2ss_udc *udc)
{
	int	i;

	INIT_LIST_HEAD(&udc->gadget.ep_list);
	udc->gadget.ep0 = &udc->ep[0].ep;

	for (i = 0; i < NUM_ENDPOINTS; i++) {
		struct nbu2ss_ep *ep = &udc->ep[i];

		ep->udc = udc;
		ep->desc = NULL;

		ep->ep.driver_data = NULL;
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &nbu2ss_ep_ops;

		usb_ep_set_maxpacket_limit(&ep->ep,
					   i == 0 ? EP0_PACKETSIZE
					   : EP_PACKETSIZE);

		list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		INIT_LIST_HEAD(&ep->queue);
	}

	list_del_init(&udc->ep[0].ep.ep_list);
}
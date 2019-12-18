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
struct TYPE_4__ {int /*<<< orphan*/  ep_list; TYPE_3__* ep0; } ;
struct isp1760_udc {TYPE_1__ gadget; struct isp1760_ep* ep; } ;
struct TYPE_5__ {int type_control; int dir_in; int dir_out; int type_iso; int type_bulk; int type_int; } ;
struct TYPE_6__ {TYPE_2__ caps; int /*<<< orphan*/  ep_list; int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; } ;
struct isp1760_ep {unsigned int addr; int maxpacket; TYPE_3__ ep; int /*<<< orphan*/  name; int /*<<< orphan*/ * desc; int /*<<< orphan*/  queue; struct isp1760_udc* udc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct isp1760_ep*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int USB_DIR_IN ; 
 unsigned int USB_DIR_OUT ; 
 int /*<<< orphan*/  isp1760_ep_ops ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,int) ; 

__attribute__((used)) static void isp1760_udc_init_eps(struct isp1760_udc *udc)
{
	unsigned int i;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	for (i = 0; i < ARRAY_SIZE(udc->ep); ++i) {
		struct isp1760_ep *ep = &udc->ep[i];
		unsigned int ep_num = (i + 1) / 2;
		bool is_in = !(i & 1);

		ep->udc = udc;

		INIT_LIST_HEAD(&ep->queue);

		ep->addr = (ep_num && is_in ? USB_DIR_IN : USB_DIR_OUT)
			 | ep_num;
		ep->desc = NULL;

		sprintf(ep->name, "ep%u%s", ep_num,
			ep_num ? (is_in ? "in" : "out") : "");

		ep->ep.ops = &isp1760_ep_ops;
		ep->ep.name = ep->name;

		/*
		 * Hardcode the maximum packet sizes for now, to 64 bytes for
		 * the control endpoint and 512 bytes for all other endpoints.
		 * This fits in the 8kB FIFO without double-buffering.
		 */
		if (ep_num == 0) {
			usb_ep_set_maxpacket_limit(&ep->ep, 64);
			ep->ep.caps.type_control = true;
			ep->ep.caps.dir_in = true;
			ep->ep.caps.dir_out = true;
			ep->maxpacket = 64;
			udc->gadget.ep0 = &ep->ep;
		} else {
			usb_ep_set_maxpacket_limit(&ep->ep, 512);
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_int = true;
			ep->maxpacket = 0;
			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		}

		if (is_in)
			ep->ep.caps.dir_in = true;
		else
			ep->ep.caps.dir_out = true;
	}
}
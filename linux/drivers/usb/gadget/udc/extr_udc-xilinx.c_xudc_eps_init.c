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
typedef  size_t u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ep_list; } ;
struct xusb_udc {TYPE_1__ gadget; struct xusb_ep* ep; } ;
struct TYPE_5__ {int type_iso; int type_bulk; int type_int; int type_control; int dir_in; int dir_out; } ;
struct TYPE_6__ {TYPE_2__ caps; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; int /*<<< orphan*/  ep_list; } ;
struct xusb_ep {size_t epnumber; int /*<<< orphan*/  queue; scalar_t__ maxpacket; scalar_t__ is_iso; scalar_t__ is_in; scalar_t__ offset; int /*<<< orphan*/ * desc; struct xusb_udc* udc; TYPE_3__ ep_usb; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned short EP0_MAX_PACKET ; 
 int /*<<< orphan*/  EPNAME_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ XUSB_EP0_CONFIG_OFFSET ; 
 size_t XUSB_MAX_ENDPOINTS ; 
 int /*<<< orphan*/  ep0name ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,unsigned short) ; 
 int /*<<< orphan*/  xudc_epconfig (struct xusb_ep*,struct xusb_udc*) ; 
 int /*<<< orphan*/  xusb_ep0_ops ; 
 int /*<<< orphan*/  xusb_ep_ops ; 

__attribute__((used)) static void xudc_eps_init(struct xusb_udc *udc)
{
	u32 ep_number;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	for (ep_number = 0; ep_number < XUSB_MAX_ENDPOINTS; ep_number++) {
		struct xusb_ep *ep = &udc->ep[ep_number];

		if (ep_number) {
			list_add_tail(&ep->ep_usb.ep_list,
				      &udc->gadget.ep_list);
			usb_ep_set_maxpacket_limit(&ep->ep_usb,
						  (unsigned short) ~0);
			snprintf(ep->name, EPNAME_SIZE, "ep%d", ep_number);
			ep->ep_usb.name = ep->name;
			ep->ep_usb.ops = &xusb_ep_ops;

			ep->ep_usb.caps.type_iso = true;
			ep->ep_usb.caps.type_bulk = true;
			ep->ep_usb.caps.type_int = true;
		} else {
			ep->ep_usb.name = ep0name;
			usb_ep_set_maxpacket_limit(&ep->ep_usb, EP0_MAX_PACKET);
			ep->ep_usb.ops = &xusb_ep0_ops;

			ep->ep_usb.caps.type_control = true;
		}

		ep->ep_usb.caps.dir_in = true;
		ep->ep_usb.caps.dir_out = true;

		ep->udc = udc;
		ep->epnumber = ep_number;
		ep->desc = NULL;
		/*
		 * The configuration register address offset between
		 * each endpoint is 0x10.
		 */
		ep->offset = XUSB_EP0_CONFIG_OFFSET + (ep_number * 0x10);
		ep->is_in = 0;
		ep->is_iso = 0;
		ep->maxpacket = 0;
		xudc_epconfig(ep, udc);

		/* Initialize one queue per endpoint */
		INIT_LIST_HEAD(&ep->queue);
	}
}
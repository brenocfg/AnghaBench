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
struct TYPE_4__ {int type_control; int type_iso; int type_bulk; int type_int; int dir_in; int dir_out; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep_list; TYPE_1__ caps; int /*<<< orphan*/  name; } ;
struct net2272_ep {int num; int dma; int fifo_size; scalar_t__ stopped; TYPE_3__ ep; scalar_t__ not_empty; struct net2272* dev; } ;
struct TYPE_5__ {TYPE_3__* ep0; } ;
struct net2272 {TYPE_2__ gadget; struct net2272_ep* ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dma_ep ; 
 int /*<<< orphan*/ * ep_name ; 
 int /*<<< orphan*/  net2272_ep_reset (struct net2272_ep*) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,int) ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static void
net2272_usb_reinit(struct net2272 *dev)
{
	int i;

	/* basic endpoint init */
	for (i = 0; i < 4; ++i) {
		struct net2272_ep *ep = &dev->ep[i];

		ep->ep.name = ep_name[i];
		ep->dev = dev;
		ep->num = i;
		ep->not_empty = 0;

		if (use_dma && ep->num == dma_ep)
			ep->dma = 1;

		if (i > 0 && i <= 3)
			ep->fifo_size = 512;
		else
			ep->fifo_size = 64;
		net2272_ep_reset(ep);

		if (i == 0) {
			ep->ep.caps.type_control = true;
		} else {
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_int = true;
		}

		ep->ep.caps.dir_in = true;
		ep->ep.caps.dir_out = true;
	}
	usb_ep_set_maxpacket_limit(&dev->ep[0].ep, 64);

	dev->gadget.ep0 = &dev->ep[0].ep;
	dev->ep[0].stopped = 0;
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);
}
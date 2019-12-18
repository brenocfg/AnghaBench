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
struct TYPE_5__ {int quirk_altset_not_supp; int /*<<< orphan*/  ep_list; TYPE_1__* ep0; } ;
struct pxa25x_udc {TYPE_2__ gadget; struct pxa25x_ep* ep; int /*<<< orphan*/  ep0state; } ;
struct TYPE_6__ {int /*<<< orphan*/  maxpacket; int /*<<< orphan*/ * desc; int /*<<< orphan*/  ep_list; } ;
struct pxa25x_ep {TYPE_3__ ep; scalar_t__ pio_irqs; int /*<<< orphan*/  queue; scalar_t__ stopped; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP0_IDLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t PXA_UDC_NUM_ENDPOINTS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_reinit(struct pxa25x_udc *dev)
{
	u32	i;

	/* device/ep0 records init */
	INIT_LIST_HEAD (&dev->gadget.ep_list);
	INIT_LIST_HEAD (&dev->gadget.ep0->ep_list);
	dev->ep0state = EP0_IDLE;
	dev->gadget.quirk_altset_not_supp = 1;

	/* basic endpoint records init */
	for (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		struct pxa25x_ep *ep = &dev->ep[i];

		if (i != 0)
			list_add_tail (&ep->ep.ep_list, &dev->gadget.ep_list);

		ep->ep.desc = NULL;
		ep->stopped = 0;
		INIT_LIST_HEAD (&ep->queue);
		ep->pio_irqs = 0;
		usb_ep_set_maxpacket_limit(&ep->ep, ep->ep.maxpacket);
	}

	/* the rest was statically initialized, and is read-only */
}
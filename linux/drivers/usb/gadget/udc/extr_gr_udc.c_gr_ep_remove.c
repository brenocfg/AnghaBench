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
struct gr_udc {int /*<<< orphan*/  dev; struct gr_ep* epo; struct gr_ep* epi; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxpacket_limit; } ;
struct gr_ep {int /*<<< orphan*/  tailbuf_paddr; scalar_t__ tailbuf; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gr_ep_remove(struct gr_udc *dev, int num, int is_in)
{
	struct gr_ep *ep;

	if (is_in)
		ep = &dev->epi[num];
	else
		ep = &dev->epo[num];

	if (ep->tailbuf)
		dma_free_coherent(dev->dev, ep->ep.maxpacket_limit,
				  ep->tailbuf, ep->tailbuf_paddr);
}
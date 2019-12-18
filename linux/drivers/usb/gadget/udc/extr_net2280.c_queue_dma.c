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
struct net2280_request {int /*<<< orphan*/  td_dma; struct net2280_dma* td; } ;
struct net2280_ep {int /*<<< orphan*/  td_dma; struct net2280_dma* dummy; } ;
struct net2280_dma {int /*<<< orphan*/  dmadesc; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_dma_desc (struct net2280_ep*,struct net2280_request*,int) ; 

__attribute__((used)) static inline void
queue_dma(struct net2280_ep *ep, struct net2280_request *req, int valid)
{
	struct net2280_dma	*end;
	dma_addr_t		tmp;

	/* swap new dummy for old, link; fill and maybe activate */
	end = ep->dummy;
	ep->dummy = req->td;
	req->td = end;

	tmp = ep->td_dma;
	ep->td_dma = req->td_dma;
	req->td_dma = tmp;

	end->dmadesc = cpu_to_le32 (ep->td_dma);

	fill_dma_desc(ep, req, valid);
}
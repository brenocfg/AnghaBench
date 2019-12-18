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
struct cdns3_trb {int control; int /*<<< orphan*/  buffer; } ;
struct cdns3_endpoint {int num_trbs; int /*<<< orphan*/  trb_pool_dma; struct cdns3_trb* trb_pool; int /*<<< orphan*/  num; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {int /*<<< orphan*/  sysdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA32 ; 
 int /*<<< orphan*/  TRB_BUFFER (int /*<<< orphan*/ ) ; 
 int TRB_CYCLE ; 
 int /*<<< orphan*/  TRB_LINK ; 
 int TRB_SIZE ; 
 int TRB_TOGGLE ; 
 int TRB_TYPE (int /*<<< orphan*/ ) ; 
 int cdns3_ring_size (struct cdns3_endpoint*) ; 
 struct cdns3_trb* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct cdns3_trb*,int /*<<< orphan*/ ,int) ; 

int cdns3_allocate_trb_pool(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	int ring_size = cdns3_ring_size(priv_ep);
	struct cdns3_trb *link_trb;

	if (!priv_ep->trb_pool) {
		priv_ep->trb_pool = dma_alloc_coherent(priv_dev->sysdev,
						       ring_size,
						       &priv_ep->trb_pool_dma,
						       GFP_DMA32 | GFP_ATOMIC);
		if (!priv_ep->trb_pool)
			return -ENOMEM;
	} else {
		memset(priv_ep->trb_pool, 0, ring_size);
	}

	if (!priv_ep->num)
		return 0;

	priv_ep->num_trbs = ring_size / TRB_SIZE;
	/* Initialize the last TRB as Link TRB. */
	link_trb = (priv_ep->trb_pool + (priv_ep->num_trbs - 1));
	link_trb->buffer = TRB_BUFFER(priv_ep->trb_pool_dma);
	link_trb->control = TRB_CYCLE | TRB_TYPE(TRB_LINK) | TRB_TOGGLE;

	return 0;
}
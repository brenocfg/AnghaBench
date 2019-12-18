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
struct TYPE_2__ {scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct musb_request {scalar_t__ map_state; scalar_t__ tx; TYPE_1__ request; struct musb_ep* ep; } ;
struct musb_ep {int /*<<< orphan*/  dma; } ;
struct musb {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MUSB_MAPPED ; 
 scalar_t__ UN_MAPPED ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_buffer_mapped (struct musb_request*) ; 

__attribute__((used)) static inline void unmap_dma_buffer(struct musb_request *request,
				struct musb *musb)
{
	struct musb_ep *musb_ep = request->ep;

	if (!is_buffer_mapped(request) || !musb_ep->dma)
		return;

	if (request->request.dma == DMA_ADDR_INVALID) {
		dev_vdbg(musb->controller,
				"not unmapping a never mapped buffer\n");
		return;
	}
	if (request->map_state == MUSB_MAPPED) {
		dma_unmap_single(musb->controller,
			request->request.dma,
			request->request.length,
			request->tx
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		request->request.dma = DMA_ADDR_INVALID;
	} else { /* PRE_MAPPED */
		dma_sync_single_for_cpu(musb->controller,
			request->request.dma,
			request->request.length,
			request->tx
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
	}
	request->map_state = UN_MAPPED;
}
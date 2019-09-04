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
struct TYPE_6__ {size_t size; int /*<<< orphan*/ * mem; int /*<<< orphan*/  dma; } ;
struct rcar_dmac_desc {TYPE_3__ hwdescs; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct rcar_dmac_chan {TYPE_2__ chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_dmac_realloc_hwdesc(struct rcar_dmac_chan *chan,
				     struct rcar_dmac_desc *desc, size_t size)
{
	/*
	 * dma_alloc_coherent() allocates memory in page size increments. To
	 * avoid reallocating the hardware descriptors when the allocated size
	 * wouldn't change align the requested size to a multiple of the page
	 * size.
	 */
	size = PAGE_ALIGN(size);

	if (desc->hwdescs.size == size)
		return;

	if (desc->hwdescs.mem) {
		dma_free_coherent(chan->chan.device->dev, desc->hwdescs.size,
				  desc->hwdescs.mem, desc->hwdescs.dma);
		desc->hwdescs.mem = NULL;
		desc->hwdescs.size = 0;
	}

	if (!size)
		return;

	desc->hwdescs.mem = dma_alloc_coherent(chan->chan.device->dev, size,
					       &desc->hwdescs.dma, GFP_NOWAIT);
	if (!desc->hwdescs.mem)
		return;

	desc->hwdescs.size = size;
}
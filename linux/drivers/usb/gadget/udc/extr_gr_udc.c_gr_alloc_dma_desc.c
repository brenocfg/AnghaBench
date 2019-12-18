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
struct gr_ep {TYPE_1__* dev; } ;
struct gr_dma_desc {int /*<<< orphan*/  paddr; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  desc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct gr_dma_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gr_dma_desc *gr_alloc_dma_desc(struct gr_ep *ep, gfp_t gfp_flags)
{
	dma_addr_t paddr;
	struct gr_dma_desc *dma_desc;

	dma_desc = dma_pool_zalloc(ep->dev->desc_pool, gfp_flags, &paddr);
	if (!dma_desc) {
		dev_err(ep->dev->dev, "Could not allocate from DMA pool\n");
		return NULL;
	}

	dma_desc->paddr = paddr;

	return dma_desc;
}
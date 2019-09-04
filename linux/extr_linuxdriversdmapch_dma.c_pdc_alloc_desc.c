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
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_submit; } ;
struct pch_dma_desc {TYPE_1__ txd; int /*<<< orphan*/  tx_list; } ;
struct pch_dma {int /*<<< orphan*/  pool; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,struct dma_chan*) ; 
 struct pch_dma_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_tx_submit ; 
 struct pch_dma* to_pd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pch_dma_desc *pdc_alloc_desc(struct dma_chan *chan, gfp_t flags)
{
	struct pch_dma_desc *desc = NULL;
	struct pch_dma *pd = to_pd(chan->device);
	dma_addr_t addr;

	desc = dma_pool_zalloc(pd->pool, flags, &addr);
	if (desc) {
		INIT_LIST_HEAD(&desc->tx_list);
		dma_async_tx_descriptor_init(&desc->txd, chan);
		desc->txd.tx_submit = pd_tx_submit;
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.phys = addr;
	}

	return desc;
}
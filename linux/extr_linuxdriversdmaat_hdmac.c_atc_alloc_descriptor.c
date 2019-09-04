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
struct dma_chan {int /*<<< orphan*/  device; } ;
struct at_dma {int /*<<< orphan*/  dma_desc_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  tx_submit; int /*<<< orphan*/  flags; } ;
struct at_desc {TYPE_1__ txd; int /*<<< orphan*/  tx_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atc_tx_submit ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,struct dma_chan*) ; 
 struct at_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct at_dma* to_at_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct at_desc *atc_alloc_descriptor(struct dma_chan *chan,
					    gfp_t gfp_flags)
{
	struct at_desc	*desc = NULL;
	struct at_dma	*atdma = to_at_dma(chan->device);
	dma_addr_t phys;

	desc = dma_pool_zalloc(atdma->dma_desc_pool, gfp_flags, &phys);
	if (desc) {
		INIT_LIST_HEAD(&desc->tx_list);
		dma_async_tx_descriptor_init(&desc->txd, chan);
		/* txd.flags will be overwritten in prep functions */
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.tx_submit = atc_tx_submit;
		desc->txd.phys = phys;
	}

	return desc;
}
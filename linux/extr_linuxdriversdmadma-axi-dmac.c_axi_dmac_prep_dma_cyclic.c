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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct axi_dmac_desc {int cyclic; int /*<<< orphan*/  vdesc; TYPE_1__* sg; } ;
struct axi_dmac_chan {int direction; int /*<<< orphan*/  vchan; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;
struct TYPE_2__ {size_t dest_addr; size_t src_addr; size_t x_len; int y_len; } ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 struct axi_dmac_desc* axi_dmac_alloc_desc (unsigned int) ; 
 int /*<<< orphan*/  axi_dmac_check_addr (struct axi_dmac_chan*,size_t) ; 
 int /*<<< orphan*/  axi_dmac_check_len (struct axi_dmac_chan*,size_t) ; 
 struct axi_dmac_chan* to_axi_dmac_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *axi_dmac_prep_dma_cyclic(
	struct dma_chan *c, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	struct axi_dmac_desc *desc;
	unsigned int num_periods, i;

	if (direction != chan->direction)
		return NULL;

	if (!axi_dmac_check_len(chan, buf_len) ||
	    !axi_dmac_check_addr(chan, buf_addr))
		return NULL;

	if (period_len == 0 || buf_len % period_len)
		return NULL;

	num_periods = buf_len / period_len;

	desc = axi_dmac_alloc_desc(num_periods);
	if (!desc)
		return NULL;

	for (i = 0; i < num_periods; i++) {
		if (direction == DMA_DEV_TO_MEM)
			desc->sg[i].dest_addr = buf_addr;
		else
			desc->sg[i].src_addr = buf_addr;
		desc->sg[i].x_len = period_len;
		desc->sg[i].y_len = 1;
		buf_addr += period_len;
	}

	desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
}
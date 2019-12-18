#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gdma_dmaengine_chan {int /*<<< orphan*/  vchan; int /*<<< orphan*/  burst_size; } ;
struct gdma_dma_desc {size_t residue; unsigned int num_sgs; int cyclic; int /*<<< orphan*/  vdesc; int /*<<< orphan*/  direction; TYPE_2__* sg; } ;
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_4__ {size_t len; void* dst_addr; void* src_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (size_t,size_t) ; 
 int /*<<< orphan*/  DMA_MEM_TO_MEM ; 
 size_t GDMA_REG_CTRL0_TX_MASK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdma_dma_maxburst (size_t) ; 
 struct gdma_dma_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg ; 
 int /*<<< orphan*/  struct_size (struct gdma_dma_desc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct gdma_dmaengine_chan* to_gdma_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *gdma_dma_prep_dma_memcpy(
		struct dma_chan *c, dma_addr_t dest, dma_addr_t src,
		size_t len, unsigned long flags)
{
	struct gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	struct gdma_dma_desc *desc;
	unsigned int num_periods, i;
	size_t xfer_count;

	if (len <= 0)
		return NULL;

	chan->burst_size = gdma_dma_maxburst(len >> 2);

	xfer_count = GDMA_REG_CTRL0_TX_MASK;
	num_periods = DIV_ROUND_UP(len, xfer_count);

	desc = kzalloc(struct_size(desc, sg, num_periods), GFP_ATOMIC);
	if (!desc) {
		dev_err(c->device->dev, "alloc memcpy decs error\n");
		return NULL;
	}
	desc->residue = len;

	for (i = 0; i < num_periods; i++) {
		desc->sg[i].src_addr = src;
		desc->sg[i].dst_addr = dest;
		if (len > xfer_count)
			desc->sg[i].len = xfer_count;
		else
			desc->sg[i].len = len;
		src += desc->sg[i].len;
		dest += desc->sg[i].len;
		len -= desc->sg[i].len;
	}

	desc->num_sgs = num_periods;
	desc->direction = DMA_MEM_TO_MEM;
	desc->cyclic = false;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
}
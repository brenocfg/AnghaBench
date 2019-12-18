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
struct gdma_dmaengine_chan {int /*<<< orphan*/  vchan; } ;
struct gdma_dma_desc {size_t residue; unsigned int num_sgs; int direction; int cyclic; int /*<<< orphan*/  vdesc; TYPE_2__* sg; } ;
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;
struct TYPE_4__ {size_t src_addr; size_t dst_addr; size_t len; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 size_t GDMA_REG_CTRL0_TX_MASK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (struct gdma_dma_desc*) ; 
 struct gdma_dma_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg ; 
 int /*<<< orphan*/  struct_size (struct gdma_dma_desc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct gdma_dmaengine_chan* to_gdma_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *gdma_dma_prep_dma_cyclic(
	struct dma_chan *c, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct gdma_dmaengine_chan *chan = to_gdma_dma_chan(c);
	struct gdma_dma_desc *desc;
	unsigned int num_periods, i;

	if (buf_len % period_len)
		return NULL;

	if (period_len > GDMA_REG_CTRL0_TX_MASK) {
		dev_err(c->device->dev, "cyclic len too large %d\n",
			period_len);
		return NULL;
	}

	num_periods = buf_len / period_len;
	desc = kzalloc(struct_size(desc, sg, num_periods), GFP_ATOMIC);
	if (!desc) {
		dev_err(c->device->dev, "alloc cyclic decs error\n");
		return NULL;
	}
	desc->residue = buf_len;

	for (i = 0; i < num_periods; i++) {
		if (direction == DMA_MEM_TO_DEV) {
			desc->sg[i].src_addr = buf_addr;
		} else if (direction == DMA_DEV_TO_MEM) {
			desc->sg[i].dst_addr = buf_addr;
		} else {
			dev_err(c->device->dev, "direction type %d error\n",
				direction);
			goto free_desc;
		}
		desc->sg[i].len = period_len;
		buf_addr += period_len;
	}

	desc->num_sgs = num_periods;
	desc->direction = direction;
	desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

free_desc:
	kfree(desc);
	return NULL;
}
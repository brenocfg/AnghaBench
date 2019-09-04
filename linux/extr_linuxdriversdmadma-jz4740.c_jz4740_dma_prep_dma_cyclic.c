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
struct jz4740_dmaengine_chan {int /*<<< orphan*/  vchan; } ;
struct jz4740_dma_desc {unsigned int num_sgs; int direction; int cyclic; int /*<<< orphan*/  vdesc; TYPE_1__* sg; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;
struct TYPE_2__ {size_t addr; size_t len; } ;

/* Variables and functions */
 struct jz4740_dma_desc* jz4740_dma_alloc_desc (unsigned int) ; 
 struct jz4740_dmaengine_chan* to_jz4740_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *jz4740_dma_prep_dma_cyclic(
	struct dma_chan *c, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct jz4740_dmaengine_chan *chan = to_jz4740_dma_chan(c);
	struct jz4740_dma_desc *desc;
	unsigned int num_periods, i;

	if (buf_len % period_len)
		return NULL;

	num_periods = buf_len / period_len;

	desc = jz4740_dma_alloc_desc(num_periods);
	if (!desc)
		return NULL;

	for (i = 0; i < num_periods; i++) {
		desc->sg[i].addr = buf_addr;
		desc->sg[i].len = period_len;
		buf_addr += period_len;
	}

	desc->num_sgs = num_periods;
	desc->direction = direction;
	desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
}
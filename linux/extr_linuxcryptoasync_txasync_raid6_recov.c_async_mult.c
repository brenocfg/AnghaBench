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
typedef  size_t u8 ;
struct page {int dummy; } ;
struct dmaengine_unmap_data {size_t len; void** addr; int /*<<< orphan*/  bidi_cnt; int /*<<< orphan*/  to_cnt; } ;
struct dma_device {struct dma_async_tx_descriptor* (* device_prep_dma_pq ) (struct dma_chan*,void**,void**,int,size_t*,size_t,int) ;struct device* dev; } ;
struct dma_chan {struct dma_device* device; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct device {int dummy; } ;
struct async_submit_ctl {int flags; int /*<<< orphan*/  depend_tx; } ;
typedef  enum dma_ctrl_flags { ____Placeholder_dma_ctrl_flags } dma_ctrl_flags ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ASYNC_TX_FENCE ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_PQ ; 
 int DMA_PREP_FENCE ; 
 int DMA_PREP_PQ_DISABLE_P ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 struct dma_chan* async_tx_find_channel (struct async_submit_ctl*,int /*<<< orphan*/ ,struct page**,int,struct page**,int,size_t) ; 
 int /*<<< orphan*/  async_tx_quiesce (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_tx_submit (struct dma_chan*,struct dma_async_tx_descriptor*,struct async_submit_ctl*) ; 
 void* dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_unmap (struct dma_async_tx_descriptor*,struct dmaengine_unmap_data*) ; 
 struct dmaengine_unmap_data* dmaengine_get_unmap_data (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_unmap_put (struct dmaengine_unmap_data*) ; 
 size_t* page_address (struct page*) ; 
 size_t** raid6_gfmul ; 
 struct dma_async_tx_descriptor* stub1 (struct dma_chan*,void**,void**,int,size_t*,size_t,int) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
async_mult(struct page *dest, struct page *src, u8 coef, size_t len,
	   struct async_submit_ctl *submit)
{
	struct dma_chan *chan = async_tx_find_channel(submit, DMA_PQ,
						      &dest, 1, &src, 1, len);
	struct dma_device *dma = chan ? chan->device : NULL;
	struct dmaengine_unmap_data *unmap = NULL;
	const u8 *qmul; /* Q multiplier table */
	u8 *d, *s;

	if (dma)
		unmap = dmaengine_get_unmap_data(dma->dev, 3, GFP_NOWAIT);

	if (unmap) {
		dma_addr_t dma_dest[2];
		struct device *dev = dma->dev;
		struct dma_async_tx_descriptor *tx;
		enum dma_ctrl_flags dma_flags = DMA_PREP_PQ_DISABLE_P;

		if (submit->flags & ASYNC_TX_FENCE)
			dma_flags |= DMA_PREP_FENCE;
		unmap->addr[0] = dma_map_page(dev, src, 0, len, DMA_TO_DEVICE);
		unmap->to_cnt++;
		unmap->addr[1] = dma_map_page(dev, dest, 0, len, DMA_BIDIRECTIONAL);
		dma_dest[1] = unmap->addr[1];
		unmap->bidi_cnt++;
		unmap->len = len;

		/* this looks funny, but the engine looks for Q at
		 * dma_dest[1] and ignores dma_dest[0] as a dest
		 * due to DMA_PREP_PQ_DISABLE_P
		 */
		tx = dma->device_prep_dma_pq(chan, dma_dest, unmap->addr,
					     1, &coef, len, dma_flags);

		if (tx) {
			dma_set_unmap(tx, unmap);
			dmaengine_unmap_put(unmap);
			async_tx_submit(chan, tx, submit);
			return tx;
		}

		/* could not get a descriptor, unmap and fall through to
		 * the synchronous path
		 */
		dmaengine_unmap_put(unmap);
	}

	/* no channel available, or failed to allocate a descriptor, so
	 * perform the operation synchronously
	 */
	async_tx_quiesce(&submit->depend_tx);
	qmul  = raid6_gfmul[coef];
	d = page_address(dest);
	s = page_address(src);

	while (len--)
		*d++ = qmul[*s++];

	return NULL;
}
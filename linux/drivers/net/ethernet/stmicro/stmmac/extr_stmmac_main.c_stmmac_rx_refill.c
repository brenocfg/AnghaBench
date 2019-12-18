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
typedef  size_t u32 ;
struct stmmac_rx_queue {unsigned int dirty_rx; scalar_t__ rx_count_frames; scalar_t__ rx_tail_addr; scalar_t__ dma_rx_phy; int /*<<< orphan*/  page_pool; struct dma_desc* dma_rx; scalar_t__ dma_erx; struct stmmac_rx_buffer* buf_pool; } ;
struct stmmac_rx_buffer {void* sec_addr; void* addr; void* page; void* sec_page; } ;
struct stmmac_priv {scalar_t__ rx_coal_frames; int /*<<< orphan*/  ioaddr; scalar_t__ use_riwt; int /*<<< orphan*/  device; scalar_t__ sph; scalar_t__ extend_desc; int /*<<< orphan*/  dma_buf_sz; struct stmmac_rx_queue* rx_queue; } ;
struct dma_desc {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_RX_SIZE ; 
 int PAGE_SIZE ; 
 unsigned int STMMAC_GET_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 void* page_pool_dev_alloc_pages (int /*<<< orphan*/ ) ; 
 void* page_pool_get_dma_addr (void*) ; 
 int /*<<< orphan*/  stmmac_refill_desc3 (struct stmmac_priv*,struct stmmac_rx_queue*,struct dma_desc*) ; 
 int stmmac_rx_dirty (struct stmmac_priv*,size_t) ; 
 int /*<<< orphan*/  stmmac_set_desc_addr (struct stmmac_priv*,struct dma_desc*,void*) ; 
 int /*<<< orphan*/  stmmac_set_desc_sec_addr (struct stmmac_priv*,struct dma_desc*,void*) ; 
 int /*<<< orphan*/  stmmac_set_rx_owner (struct stmmac_priv*,struct dma_desc*,int) ; 
 int /*<<< orphan*/  stmmac_set_rx_tail_ptr (struct stmmac_priv*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 

__attribute__((used)) static inline void stmmac_rx_refill(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	int len, dirty = stmmac_rx_dirty(priv, queue);
	unsigned int entry = rx_q->dirty_rx;

	len = DIV_ROUND_UP(priv->dma_buf_sz, PAGE_SIZE) * PAGE_SIZE;

	while (dirty-- > 0) {
		struct stmmac_rx_buffer *buf = &rx_q->buf_pool[entry];
		struct dma_desc *p;
		bool use_rx_wd;

		if (priv->extend_desc)
			p = (struct dma_desc *)(rx_q->dma_erx + entry);
		else
			p = rx_q->dma_rx + entry;

		if (!buf->page) {
			buf->page = page_pool_dev_alloc_pages(rx_q->page_pool);
			if (!buf->page)
				break;
		}

		if (priv->sph && !buf->sec_page) {
			buf->sec_page = page_pool_dev_alloc_pages(rx_q->page_pool);
			if (!buf->sec_page)
				break;

			buf->sec_addr = page_pool_get_dma_addr(buf->sec_page);

			dma_sync_single_for_device(priv->device, buf->sec_addr,
						   len, DMA_FROM_DEVICE);
		}

		buf->addr = page_pool_get_dma_addr(buf->page);

		/* Sync whole allocation to device. This will invalidate old
		 * data.
		 */
		dma_sync_single_for_device(priv->device, buf->addr, len,
					   DMA_FROM_DEVICE);

		stmmac_set_desc_addr(priv, p, buf->addr);
		stmmac_set_desc_sec_addr(priv, p, buf->sec_addr);
		stmmac_refill_desc3(priv, rx_q, p);

		rx_q->rx_count_frames++;
		rx_q->rx_count_frames += priv->rx_coal_frames;
		if (rx_q->rx_count_frames > priv->rx_coal_frames)
			rx_q->rx_count_frames = 0;
		use_rx_wd = priv->use_riwt && rx_q->rx_count_frames;

		dma_wmb();
		stmmac_set_rx_owner(priv, p, use_rx_wd);

		entry = STMMAC_GET_ENTRY(entry, DMA_RX_SIZE);
	}
	rx_q->dirty_rx = entry;
	rx_q->rx_tail_addr = rx_q->dma_rx_phy +
			    (rx_q->dirty_rx * sizeof(struct dma_desc));
	stmmac_set_rx_tail_ptr(priv, priv->ioaddr, rx_q->rx_tail_addr, queue);
}
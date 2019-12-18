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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct gfar_rx_buff {int page_offset; struct page* page; int /*<<< orphan*/  dma; } ;
struct gfar_priv_rx_q {size_t next_to_clean; int /*<<< orphan*/  dev; struct gfar_rx_buff* rx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFAR_RXB_TRUESIZE ; 
 int /*<<< orphan*/  GFAR_SKBFRAG_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RXBUF_ALIGNMENT ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gfar_add_rx_frag (struct gfar_rx_buff*,int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  gfar_reuse_rx_page (struct gfar_priv_rx_q*,struct gfar_rx_buff*) ; 
 int /*<<< orphan*/  gfar_rx_alloc_err (struct gfar_priv_rx_q*) ; 
 scalar_t__ likely (int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *gfar_get_next_rxbuff(struct gfar_priv_rx_q *rx_queue,
					    u32 lstatus, struct sk_buff *skb)
{
	struct gfar_rx_buff *rxb = &rx_queue->rx_buff[rx_queue->next_to_clean];
	struct page *page = rxb->page;
	bool first = false;

	if (likely(!skb)) {
		void *buff_addr = page_address(page) + rxb->page_offset;

		skb = build_skb(buff_addr, GFAR_SKBFRAG_SIZE);
		if (unlikely(!skb)) {
			gfar_rx_alloc_err(rx_queue);
			return NULL;
		}
		skb_reserve(skb, RXBUF_ALIGNMENT);
		first = true;
	}

	dma_sync_single_range_for_cpu(rx_queue->dev, rxb->dma, rxb->page_offset,
				      GFAR_RXB_TRUESIZE, DMA_FROM_DEVICE);

	if (gfar_add_rx_frag(rxb, lstatus, skb, first)) {
		/* reuse the free half of the page */
		gfar_reuse_rx_page(rx_queue, rxb);
	} else {
		/* page cannot be reused, unmap it */
		dma_unmap_page(rx_queue->dev, rxb->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
	}

	/* clear rxb content */
	rxb->page = NULL;

	return skb;
}
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
typedef  scalar_t__ u16 ;
struct page {int dummy; } ;
struct netsec_priv {int /*<<< orphan*/  dev; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {int /*<<< orphan*/  page_pool; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t NETSEC_RING_RX ; 
 scalar_t__ NETSEC_RXBUF_HEADROOM ; 
 scalar_t__ NETSEC_RX_BUF_NON_DATA ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 void* page_address (struct page*) ; 
 struct page* page_pool_dev_alloc_pages (int /*<<< orphan*/ ) ; 
 scalar_t__ page_pool_get_dma_addr (struct page*) ; 
 int page_pool_get_dma_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *netsec_alloc_rx_data(struct netsec_priv *priv,
				  dma_addr_t *dma_handle, u16 *desc_len)

{

	struct netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	enum dma_data_direction dma_dir;
	struct page *page;

	page = page_pool_dev_alloc_pages(dring->page_pool);
	if (!page)
		return NULL;

	/* We allocate the same buffer length for XDP and non-XDP cases.
	 * page_pool API will map the whole page, skip what's needed for
	 * network payloads and/or XDP
	 */
	*dma_handle = page_pool_get_dma_addr(page) + NETSEC_RXBUF_HEADROOM;
	/* Make sure the incoming payload fits in the page for XDP and non-XDP
	 * cases and reserve enough space for headroom + skb_shared_info
	 */
	*desc_len = PAGE_SIZE - NETSEC_RX_BUF_NON_DATA;
	dma_dir = page_pool_get_dma_dir(dring->page_pool);
	dma_sync_single_for_device(priv->dev, *dma_handle, *desc_len, dma_dir);

	return page_address(page);
}
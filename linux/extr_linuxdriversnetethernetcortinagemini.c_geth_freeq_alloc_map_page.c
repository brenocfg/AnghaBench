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
struct page {int dummy; } ;
struct TYPE_2__ {void* buf_adr; } ;
struct gmac_rxdesc {TYPE_1__ word2; } ;
struct gmac_queue_page {struct page* page; void* mapping; } ;
struct gemini_ethernet {int freeq_frag_order; int /*<<< orphan*/  dev; struct gmac_rxdesc* freeq_ring; struct gmac_queue_page* freeq_pages; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,int,...) ; 
 void* dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static struct page *geth_freeq_alloc_map_page(struct gemini_ethernet *geth,
					      int pn)
{
	struct gmac_rxdesc *freeq_entry;
	struct gmac_queue_page *gpage;
	unsigned int fpp_order;
	unsigned int frag_len;
	dma_addr_t mapping;
	struct page *page;
	int i;

	/* First allocate and DMA map a single page */
	page = alloc_page(GFP_ATOMIC);
	if (!page)
		return NULL;

	mapping = dma_map_single(geth->dev, page_address(page),
				 PAGE_SIZE, DMA_FROM_DEVICE);
	if (dma_mapping_error(geth->dev, mapping)) {
		put_page(page);
		return NULL;
	}

	/* The assign the page mapping (physical address) to the buffer address
	 * in the hardware queue. PAGE_SHIFT on ARM is 12 (1 page is 4096 bytes,
	 * 4k), and the default RX frag order is 11 (fragments are up 20 2048
	 * bytes, 2k) so fpp_order (fragments per page order) is default 1. Thus
	 * each page normally needs two entries in the queue.
	 */
	frag_len = 1 << geth->freeq_frag_order; /* Usually 2048 */
	fpp_order = PAGE_SHIFT - geth->freeq_frag_order;
	freeq_entry = geth->freeq_ring + (pn << fpp_order);
	dev_dbg(geth->dev, "allocate page %d fragment length %d fragments per page %d, freeq entry %p\n",
		 pn, frag_len, (1 << fpp_order), freeq_entry);
	for (i = (1 << fpp_order); i > 0; i--) {
		freeq_entry->word2.buf_adr = mapping;
		freeq_entry++;
		mapping += frag_len;
	}

	/* If the freeq entry already has a page mapped, then unmap it. */
	gpage = &geth->freeq_pages[pn];
	if (gpage->page) {
		mapping = geth->freeq_ring[pn << fpp_order].word2.buf_adr;
		dma_unmap_single(geth->dev, mapping, frag_len, DMA_FROM_DEVICE);
		/* This should be the last reference to the page so it gets
		 * released
		 */
		put_page(gpage->page);
	}

	/* Then put our new mapping into the page table */
	dev_dbg(geth->dev, "page %d, DMA addr: %08x, page %p\n",
		pn, (unsigned int)mapping, page);
	gpage->mapping = mapping;
	gpage->page = page;

	return page;
}
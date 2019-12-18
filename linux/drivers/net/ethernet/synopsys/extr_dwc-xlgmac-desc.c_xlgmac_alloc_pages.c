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
struct xlgmac_pdata {int /*<<< orphan*/  dev; } ;
struct xlgmac_page_alloc {int pages_len; int /*<<< orphan*/  pages_dma; scalar_t__ pages_offset; struct page* pages; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 struct page* alloc_pages (int,int) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int xlgmac_alloc_pages(struct xlgmac_pdata *pdata,
			      struct xlgmac_page_alloc *pa,
			      gfp_t gfp, int order)
{
	struct page *pages = NULL;
	dma_addr_t pages_dma;

	/* Try to obtain pages, decreasing order if necessary */
	gfp |= __GFP_COMP | __GFP_NOWARN;
	while (order >= 0) {
		pages = alloc_pages(gfp, order);
		if (pages)
			break;

		order--;
	}
	if (!pages)
		return -ENOMEM;

	/* Map the pages */
	pages_dma = dma_map_page(pdata->dev, pages, 0,
				 PAGE_SIZE << order, DMA_FROM_DEVICE);
	if (dma_mapping_error(pdata->dev, pages_dma)) {
		put_page(pages);
		return -ENOMEM;
	}

	pa->pages = pages;
	pa->pages_len = PAGE_SIZE << order;
	pa->pages_offset = 0;
	pa->pages_dma = pages_dma;

	return 0;
}
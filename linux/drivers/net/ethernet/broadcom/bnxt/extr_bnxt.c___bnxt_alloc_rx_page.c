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
struct device {int dummy; } ;
struct bnxt_rx_ring_info {int /*<<< orphan*/  page_pool; } ;
struct bnxt {scalar_t__ rx_dma_offset; int /*<<< orphan*/  rx_dir; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_page_attrs (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 struct page* page_pool_dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pool_recycle_direct (int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static struct page *__bnxt_alloc_rx_page(struct bnxt *bp, dma_addr_t *mapping,
					 struct bnxt_rx_ring_info *rxr,
					 gfp_t gfp)
{
	struct device *dev = &bp->pdev->dev;
	struct page *page;

	page = page_pool_dev_alloc_pages(rxr->page_pool);
	if (!page)
		return NULL;

	*mapping = dma_map_page_attrs(dev, page, 0, PAGE_SIZE, bp->rx_dir,
				      DMA_ATTR_WEAK_ORDERING);
	if (dma_mapping_error(dev, *mapping)) {
		page_pool_recycle_direct(rxr->page_pool, page);
		return NULL;
	}
	*mapping += bp->rx_dma_offset;
	return page;
}
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
struct TYPE_2__ {unsigned int num_pages; struct page** pages; } ;
struct ttm_dma_tt {TYPE_1__ ttm; int /*<<< orphan*/ * dma_address; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (TYPE_1__*) ; 

void ttm_unmap_and_unpopulate_pages(struct device *dev, struct ttm_dma_tt *tt)
{
	unsigned i, j;

	for (i = 0; i < tt->ttm.num_pages;) {
		struct page *p = tt->ttm.pages[i];
		size_t num_pages = 1;

		if (!tt->dma_address[i] || !tt->ttm.pages[i]) {
			++i;
			continue;
		}

		for (j = i + 1; j < tt->ttm.num_pages; ++j) {
			if (++p != tt->ttm.pages[j])
				break;

			++num_pages;
		}

		dma_unmap_page(dev, tt->dma_address[i], num_pages * PAGE_SIZE,
			       DMA_BIDIRECTIONAL);

		i += num_pages;
	}
	ttm_pool_unpopulate(&tt->ttm);
}
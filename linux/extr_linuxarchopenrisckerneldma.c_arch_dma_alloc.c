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
struct mm_walk {int /*<<< orphan*/ * mm; int /*<<< orphan*/  pte_entry; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  __pa (void*) ; 
 void* alloc_pages_exact (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages_exact (void*,size_t) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  page_set_nocache ; 
 scalar_t__ walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 

void *
arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	unsigned long va;
	void *page;
	struct mm_walk walk = {
		.pte_entry = page_set_nocache,
		.mm = &init_mm
	};

	page = alloc_pages_exact(size, gfp);
	if (!page)
		return NULL;

	/* This gives us the real physical address of the first page. */
	*dma_handle = __pa(page);

	va = (unsigned long)page;

	if ((attrs & DMA_ATTR_NON_CONSISTENT) == 0) {
		/*
		 * We need to iterate through the pages, clearing the dcache for
		 * them and setting the cache-inhibit bit.
		 */
		if (walk_page_range(va, va + size, &walk)) {
			free_pages_exact(page, size);
			return NULL;
		}
	}

	return (void *)va;
}
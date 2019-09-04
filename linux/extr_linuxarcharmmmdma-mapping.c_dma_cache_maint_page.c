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
struct page {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 scalar_t__ cache_is_vipt_nonaliasing () ; 
 void* kmap_atomic (struct page*) ; 
 void* kmap_high_get (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  kunmap_high (struct page*) ; 
 void* page_address (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 

__attribute__((used)) static void dma_cache_maint_page(struct page *page, unsigned long offset,
	size_t size, enum dma_data_direction dir,
	void (*op)(const void *, size_t, int))
{
	unsigned long pfn;
	size_t left = size;

	pfn = page_to_pfn(page) + offset / PAGE_SIZE;
	offset %= PAGE_SIZE;

	/*
	 * A single sg entry may refer to multiple physically contiguous
	 * pages.  But we still need to process highmem pages individually.
	 * If highmem is not configured then the bulk of this loop gets
	 * optimized out.
	 */
	do {
		size_t len = left;
		void *vaddr;

		page = pfn_to_page(pfn);

		if (PageHighMem(page)) {
			if (len + offset > PAGE_SIZE)
				len = PAGE_SIZE - offset;

			if (cache_is_vipt_nonaliasing()) {
				vaddr = kmap_atomic(page);
				op(vaddr + offset, len, dir);
				kunmap_atomic(vaddr);
			} else {
				vaddr = kmap_high_get(page);
				if (vaddr) {
					op(vaddr + offset, len, dir);
					kunmap_high(page);
				}
			}
		} else {
			vaddr = page_address(page) + offset;
			op(vaddr, len, dir);
		}
		offset = 0;
		pfn++;
		left -= len;
	} while (left);
}
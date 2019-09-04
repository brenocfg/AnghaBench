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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages_exact (void*,size_t) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  page_clear_nocache ; 
 int /*<<< orphan*/  walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 

void
arch_dma_free(struct device *dev, size_t size, void *vaddr,
		dma_addr_t dma_handle, unsigned long attrs)
{
	unsigned long va = (unsigned long)vaddr;
	struct mm_walk walk = {
		.pte_entry = page_clear_nocache,
		.mm = &init_mm
	};

	if ((attrs & DMA_ATTR_NON_CONSISTENT) == 0) {
		/* walk_page_range shouldn't be able to fail here */
		WARN_ON(walk_page_range(va, va + size, &walk));
	}

	free_pages_exact(vaddr, size);
}
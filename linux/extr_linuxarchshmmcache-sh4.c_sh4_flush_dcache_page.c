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
struct page {int /*<<< orphan*/  flags; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 int /*<<< orphan*/  PG_dcache_clean ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cache_one (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 scalar_t__ page_address (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 unsigned long shm_align_mask ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sh4_flush_dcache_page(void *arg)
{
	struct page *page = arg;
	unsigned long addr = (unsigned long)page_address(page);
#ifndef CONFIG_SMP
	struct address_space *mapping = page_mapping_file(page);

	if (mapping && !mapping_mapped(mapping))
		clear_bit(PG_dcache_clean, &page->flags);
	else
#endif
		flush_cache_one(CACHE_OC_ADDRESS_ARRAY |
				(addr & shm_align_mask), page_to_phys(page));

	wmb();
}
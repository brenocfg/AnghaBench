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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PG_dcache_clean ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_dcache_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_aliases (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 scalar_t__ page_address (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void flush_dcache_page(struct page *page)
{
	struct address_space *mapping;

	/*
	 * The zero page is never written to, so never has any dirty
	 * cache lines, and therefore never needs to be flushed.
	 */
	if (page == ZERO_PAGE(0))
		return;

	mapping = page_mapping_file(page);

	/* Flush this page if there are aliases. */
	if (mapping && !mapping_mapped(mapping)) {
		clear_bit(PG_dcache_clean, &page->flags);
	} else {
		__flush_dcache_page(mapping, page);
		if (mapping) {
			unsigned long start = (unsigned long)page_address(page);
			flush_aliases(mapping,  page);
			flush_icache_range(start, start + PAGE_SIZE);
		}
		set_bit(PG_dcache_clean, &page->flags);
	}
}
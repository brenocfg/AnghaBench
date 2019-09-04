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
 int /*<<< orphan*/  PG_dcache_clean ; 
 int /*<<< orphan*/  __flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 

__attribute__((used)) static void sh7705_flush_dcache_page(void *arg)
{
	struct page *page = arg;
	struct address_space *mapping = page_mapping_file(page);

	if (mapping && !mapping_mapped(mapping))
		clear_bit(PG_dcache_clean, &page->flags);
	else
		__flush_dcache_page(__pa(page_address(page)));
}
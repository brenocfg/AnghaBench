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
struct page {int /*<<< orphan*/ * mapping; } ;
struct msc {unsigned long nr_pages; scalar_t__ base; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* virt_to_page (scalar_t__) ; 

__attribute__((used)) static void msc_buffer_contig_free(struct msc *msc)
{
	unsigned long off;

	for (off = 0; off < msc->nr_pages << PAGE_SHIFT; off += PAGE_SIZE) {
		struct page *page = virt_to_page(msc->base + off);

		page->mapping = NULL;
		__free_page(page);
	}

	msc->nr_pages = 0;
}
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
struct msc {unsigned long nr_pages; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages (int,unsigned int) ; 
 unsigned int get_order (unsigned long) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned int) ; 

__attribute__((used)) static int msc_buffer_contig_alloc(struct msc *msc, unsigned long size)
{
	unsigned int order = get_order(size);
	struct page *page;

	if (!size)
		return 0;

	page = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
	if (!page)
		return -ENOMEM;

	split_page(page, order);
	msc->nr_pages = size >> PAGE_SHIFT;
	msc->base = page_address(page);
	msc->base_addr = page_to_phys(page);

	return 0;
}
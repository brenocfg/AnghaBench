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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct page* pfn_to_page (unsigned long) ; 
 int set_pages_ro (struct page*,unsigned int) ; 
 int set_pages_rw (struct page*,unsigned int) ; 

__attribute__((used)) static int
kexec_mark_range(unsigned long start, unsigned long end, bool protect)
{
	struct page *page;
	unsigned int nr_pages;

	/*
	 * For physical range: [start, end]. We must skip the unassigned
	 * crashk resource with zero-valued "end" member.
	 */
	if (!end || start > end)
		return 0;

	page = pfn_to_page(start >> PAGE_SHIFT);
	nr_pages = (end >> PAGE_SHIFT) - (start >> PAGE_SHIFT) + 1;
	if (protect)
		return set_pages_ro(page, nr_pages);
	else
		return set_pages_rw(page, nr_pages);
}
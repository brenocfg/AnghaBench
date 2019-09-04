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
struct address_space {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __flush_dcache (unsigned long,scalar_t__) ; 
 scalar_t__ page_address (struct page*) ; 

void __flush_dcache_page(struct address_space *mapping, struct page *page)
{
	/*
	 * Writeback any data associated with the kernel mapping of this
	 * page.  This ensures that data in the physical page is mutually
	 * coherent with the kernels mapping.
	 */
	unsigned long start = (unsigned long)page_address(page);

	__flush_dcache(start, start + PAGE_SIZE);
}
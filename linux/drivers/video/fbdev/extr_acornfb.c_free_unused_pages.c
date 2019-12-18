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
 unsigned int PAGE_ALIGN (unsigned int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_reserved_page (struct page*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 struct page* virt_to_page (unsigned int) ; 

__attribute__((used)) static inline void
free_unused_pages(unsigned int virtual_start, unsigned int virtual_end)
{
	int mb_freed = 0;

	/*
	 * Align addresses
	 */
	virtual_start = PAGE_ALIGN(virtual_start);
	virtual_end = PAGE_ALIGN(virtual_end);

	while (virtual_start < virtual_end) {
		struct page *page;

		/*
		 * Clear page reserved bit,
		 * set count to 1, and free
		 * the page.
		 */
		page = virt_to_page(virtual_start);
		__free_reserved_page(page);

		virtual_start += PAGE_SIZE;
		mb_freed += PAGE_SIZE / 1024;
	}

	printk("acornfb: freed %dK memory\n", mb_freed);
}
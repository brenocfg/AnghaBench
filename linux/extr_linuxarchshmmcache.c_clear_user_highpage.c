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
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __flush_purge_region (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ pages_do_alias (unsigned long,unsigned long) ; 

void clear_user_highpage(struct page *page, unsigned long vaddr)
{
	void *kaddr = kmap_atomic(page);

	clear_page(kaddr);

	if (pages_do_alias((unsigned long)kaddr, vaddr & PAGE_MASK))
		__flush_purge_region(kaddr, PAGE_SIZE);

	kunmap_atomic(kaddr);
}
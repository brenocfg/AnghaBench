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
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 int /*<<< orphan*/  sync_icache_aliases (void*,unsigned long) ; 

void arch_uprobe_copy_ixol(struct page *page, unsigned long vaddr,
		void *src, unsigned long len)
{
	void *xol_page_kaddr = kmap_atomic(page);
	void *dst = xol_page_kaddr + (vaddr & ~PAGE_MASK);

	/* Initialize the slot */
	memcpy(dst, src, len);

	/* flush caches (dcache/icache) */
	sync_icache_aliases(dst, len);

	kunmap_atomic(xol_page_kaddr);
}
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
 int /*<<< orphan*/  flush_uprobe_xol_access (struct page*,unsigned long,void*,unsigned long) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void arch_uprobe_copy_ixol(struct page *page, unsigned long vaddr,
			   void *src, unsigned long len)
{
	void *xol_page_kaddr = kmap_atomic(page);
	void *dst = xol_page_kaddr + (vaddr & ~PAGE_MASK);

	preempt_disable();

	/* Initialize the slot */
	memcpy(dst, src, len);

	/* flush caches (dcache/icache) */
	flush_uprobe_xol_access(page, vaddr, dst, len);

	preempt_enable();

	kunmap_atomic(xol_page_kaddr);
}
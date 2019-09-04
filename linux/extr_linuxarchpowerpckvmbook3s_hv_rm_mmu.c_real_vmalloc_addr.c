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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 void* __va (unsigned long) ; 
 int /*<<< orphan*/ * find_init_mm_pte (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *real_vmalloc_addr(void *x)
{
	unsigned long addr = (unsigned long) x;
	pte_t *p;
	/*
	 * assume we don't have huge pages in vmalloc space...
	 * So don't worry about THP collapse/split. Called
	 * Only in realmode with MSR_EE = 0, hence won't need irq_save/restore.
	 */
	p = find_init_mm_pte(addr, NULL);
	if (!p || !pte_present(*p))
		return NULL;
	addr = (pte_pfn(*p) << PAGE_SHIFT) | (addr & ~PAGE_MASK);
	return __va(addr);
}
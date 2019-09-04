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
struct page {int /*<<< orphan*/  pt_frag_refcount; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PMD_FRAG_NR ; 
 unsigned long PMD_FRAG_SIZE_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 scalar_t__ atomic_sub_and_test (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgtable_pmd_page_dtor (struct page*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void pmd_frag_destroy(void *pmd_frag)
{
	int count;
	struct page *page;

	page = virt_to_page(pmd_frag);
	/* drop all the pending references */
	count = ((unsigned long)pmd_frag & ~PAGE_MASK) >> PMD_FRAG_SIZE_SHIFT;
	/* We allow PTE_FRAG_NR fragments from a PTE page */
	if (atomic_sub_and_test(PMD_FRAG_NR - count, &page->pt_frag_refcount)) {
		pgtable_pmd_page_dtor(page);
		__free_page(page);
	}
}
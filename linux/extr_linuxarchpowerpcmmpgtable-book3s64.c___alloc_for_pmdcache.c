#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  pt_frag_refcount; } ;
struct TYPE_2__ {void* pmd_frag; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; TYPE_1__ context; } ;
typedef  void pmd_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL_ACCOUNT ; 
 int PMD_FRAG_NR ; 
 int PMD_FRAG_SIZE ; 
 int __GFP_ACCOUNT ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct mm_struct init_mm ; 
 scalar_t__ likely (int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pgtable_pmd_page_ctor (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pmd_t *__alloc_for_pmdcache(struct mm_struct *mm)
{
	void *ret = NULL;
	struct page *page;
	gfp_t gfp = GFP_KERNEL_ACCOUNT | __GFP_ZERO;

	if (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;
	page = alloc_page(gfp);
	if (!page)
		return NULL;
	if (!pgtable_pmd_page_ctor(page)) {
		__free_pages(page, 0);
		return NULL;
	}

	atomic_set(&page->pt_frag_refcount, 1);

	ret = page_address(page);
	/*
	 * if we support only one fragment just return the
	 * allocated page.
	 */
	if (PMD_FRAG_NR == 1)
		return ret;

	spin_lock(&mm->page_table_lock);
	/*
	 * If we find pgtable_page set, we return
	 * the allocated page with single fragement
	 * count.
	 */
	if (likely(!mm->context.pmd_frag)) {
		atomic_set(&page->pt_frag_refcount, PMD_FRAG_NR);
		mm->context.pmd_frag = ret + PMD_FRAG_SIZE;
	}
	spin_unlock(&mm->page_table_lock);

	return (pmd_t *)ret;
}
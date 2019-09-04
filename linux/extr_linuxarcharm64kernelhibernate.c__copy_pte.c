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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_pagealloc_enabled () ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkpresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _copy_pte(pte_t *dst_ptep, pte_t *src_ptep, unsigned long addr)
{
	pte_t pte = READ_ONCE(*src_ptep);

	if (pte_valid(pte)) {
		/*
		 * Resume will overwrite areas that may be marked
		 * read only (code, rodata). Clear the RDONLY bit from
		 * the temporary mappings we use during restore.
		 */
		set_pte(dst_ptep, pte_mkwrite(pte));
	} else if (debug_pagealloc_enabled() && !pte_none(pte)) {
		/*
		 * debug_pagealloc will removed the PTE_VALID bit if
		 * the page isn't in use by the resume kernel. It may have
		 * been in use by the original kernel, in which case we need
		 * to put it back in our copy to do the restore.
		 *
		 * Before marking this entry valid, check the pfn should
		 * be mapped.
		 */
		BUG_ON(!pfn_valid(pte_pfn(pte)));

		set_pte(dst_ptep, pte_mkpresent(pte_mkwrite(pte)));
	}
}
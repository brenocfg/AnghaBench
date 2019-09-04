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
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  X86_FEATURE_PGE ; 
 int /*<<< orphan*/  _PAGE_GLOBAL ; 
 int _PAGE_PRESENT ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_pte (int,int /*<<< orphan*/ ) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_vaddr (unsigned long,int /*<<< orphan*/ ) ; 

void cea_set_pte(void *cea_vaddr, phys_addr_t pa, pgprot_t flags)
{
	unsigned long va = (unsigned long) cea_vaddr;
	pte_t pte = pfn_pte(pa >> PAGE_SHIFT, flags);

	/*
	 * The cpu_entry_area is shared between the user and kernel
	 * page tables.  All of its ptes can safely be global.
	 * _PAGE_GLOBAL gets reused to help indicate PROT_NONE for
	 * non-present PTEs, so be careful not to set it in that
	 * case to avoid confusion.
	 */
	if (boot_cpu_has(X86_FEATURE_PGE) &&
	    (pgprot_val(flags) & _PAGE_PRESENT))
		pte = pte_set_flags(pte, _PAGE_GLOBAL);

	set_pte_vaddr(va, pte);
}
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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_one_kernel (unsigned long) ; 
 int /*<<< orphan*/ * fill_pmd (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * fill_pte (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_pte_vaddr(pud_t *pud, unsigned long vaddr, pte_t new_pte)
{
	pmd_t *pmd = fill_pmd(pud, vaddr);
	pte_t *pte = fill_pte(pmd, vaddr);

	set_pte(pte, new_pte);

	/*
	 * It's enough to flush this one mapping.
	 * (PGE mappings get flushed as well)
	 */
	__flush_tlb_one_kernel(vaddr);
}
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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int _PAGE_PTE ; 
 int /*<<< orphan*/  __pte (int) ; 
 int /*<<< orphan*/  __set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_protnone (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_filter (int /*<<< orphan*/ ) ; 

void set_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep,
		pte_t pte)
{
	/*
	 * When handling numa faults, we already have the pte marked
	 * _PAGE_PRESENT, but we can be sure that it is not in hpte.
	 * Hence we can use set_pte_at for them.
	 */
	VM_WARN_ON(pte_present(*ptep) && !pte_protnone(*ptep));

	/* Add the pte bit when trying to set a pte */
	pte = __pte(pte_val(pte) | _PAGE_PTE);

	/* Note: mm->context.id might not yet have been assigned as
	 * this context might not have been activated yet when this
	 * is called.
	 */
	pte = set_pte_filter(pte);

	/* Perform the setting of the PTE */
	__set_pte_at(mm, addr, ptep, pte, 0);
}
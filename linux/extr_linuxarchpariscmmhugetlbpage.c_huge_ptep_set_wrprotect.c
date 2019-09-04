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
 int /*<<< orphan*/  __set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

void huge_ptep_set_wrprotect(struct mm_struct *mm,
				unsigned long addr, pte_t *ptep)
{
	unsigned long flags;
	pte_t old_pte;

	purge_tlb_start(flags);
	old_pte = *ptep;
	__set_huge_pte_at(mm, addr, ptep, pte_wrprotect(old_pte));
	purge_tlb_end(flags);
}
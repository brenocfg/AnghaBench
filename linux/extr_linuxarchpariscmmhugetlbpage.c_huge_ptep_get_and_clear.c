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
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

pte_t huge_ptep_get_and_clear(struct mm_struct *mm, unsigned long addr,
			      pte_t *ptep)
{
	unsigned long flags;
	pte_t entry;

	purge_tlb_start(flags);
	entry = *ptep;
	__set_huge_pte_at(mm, addr, ptep, __pte(0));
	purge_tlb_end(flags);

	return entry;
}
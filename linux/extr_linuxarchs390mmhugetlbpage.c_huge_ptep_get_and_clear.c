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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  _REGION3_ENTRY_EMPTY ; 
 int _REGION_ENTRY_TYPE_MASK ; 
 int _REGION_ENTRY_TYPE_R3 ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_EMPTY ; 
 int /*<<< orphan*/  __pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pud (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmdp_xchg_direct (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pudp_xchg_direct (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

pte_t huge_ptep_get_and_clear(struct mm_struct *mm,
			      unsigned long addr, pte_t *ptep)
{
	pte_t pte = huge_ptep_get(ptep);
	pmd_t *pmdp = (pmd_t *) ptep;
	pud_t *pudp = (pud_t *) ptep;

	if ((pte_val(*ptep) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3)
		pudp_xchg_direct(mm, addr, pudp, __pud(_REGION3_ENTRY_EMPTY));
	else
		pmdp_xchg_direct(mm, addr, pmdp, __pmd(_SEGMENT_ENTRY_EMPTY));
	return pte;
}
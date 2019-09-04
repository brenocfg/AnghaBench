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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int _REGION_ENTRY_TYPE_MASK ; 
 int _REGION_ENTRY_TYPE_R3 ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  gup_huge_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 int /*<<< orphan*/  gup_pte_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pmd_index (unsigned long) ; 
 int /*<<< orphan*/  pmd_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_protnone (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_deref (int /*<<< orphan*/ ) ; 
 int pud_val (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int gup_pmd_range(pud_t *pudp, pud_t pud, unsigned long addr,
		unsigned long end, int write, struct page **pages, int *nr)
{
	unsigned long next;
	pmd_t *pmdp, pmd;

	pmdp = (pmd_t *) pudp;
	if ((pud_val(pud) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3)
		pmdp = (pmd_t *) pud_deref(pud);
	pmdp += pmd_index(addr);
	do {
		pmd = *pmdp;
		barrier();
		next = pmd_addr_end(addr, end);
		if (pmd_none(pmd))
			return 0;
		if (unlikely(pmd_large(pmd))) {
			/*
			 * NUMA hinting faults need to be handled in the GUP
			 * slowpath for accounting purposes and so that they
			 * can be serialised against THP migration.
			 */
			if (pmd_protnone(pmd))
				return 0;
			if (!gup_huge_pmd(pmdp, pmd, addr, next,
					  write, pages, nr))
				return 0;
		} else if (!gup_pte_range(pmdp, pmd, addr, next,
					  write, pages, nr))
			return 0;
	} while (pmdp++, addr = next, addr != end);

	return 1;
}
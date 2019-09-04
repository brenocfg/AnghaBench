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
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int _REGION_ENTRY_TYPE_MASK ; 
 int _REGION_ENTRY_TYPE_R2 ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  gup_huge_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 int /*<<< orphan*/  gup_pmd_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 scalar_t__ p4d_deref (int /*<<< orphan*/ ) ; 
 int p4d_val (int /*<<< orphan*/ ) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pud_index (unsigned long) ; 
 int /*<<< orphan*/  pud_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int gup_pud_range(p4d_t *p4dp, p4d_t p4d, unsigned long addr,
		unsigned long end, int write, struct page **pages, int *nr)
{
	unsigned long next;
	pud_t *pudp, pud;

	pudp = (pud_t *) p4dp;
	if ((p4d_val(p4d) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R2)
		pudp = (pud_t *) p4d_deref(p4d);
	pudp += pud_index(addr);
	do {
		pud = *pudp;
		barrier();
		next = pud_addr_end(addr, end);
		if (pud_none(pud))
			return 0;
		if (unlikely(pud_large(pud))) {
			if (!gup_huge_pud(pudp, pud, addr, next, write, pages,
					  nr))
				return 0;
		} else if (!gup_pmd_range(pudp, pud, addr, next, write, pages,
					  nr))
			return 0;
	} while (pudp++, addr = next, addr != end);

	return 1;
}
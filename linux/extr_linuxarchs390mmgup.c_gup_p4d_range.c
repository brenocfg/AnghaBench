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
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int _REGION_ENTRY_TYPE_MASK ; 
 int _REGION_ENTRY_TYPE_R1 ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  gup_pud_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  p4d_index (unsigned long) ; 
 scalar_t__ p4d_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_deref (int /*<<< orphan*/ ) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int gup_p4d_range(pgd_t *pgdp, pgd_t pgd, unsigned long addr,
		unsigned long end, int write, struct page **pages, int *nr)
{
	unsigned long next;
	p4d_t *p4dp, p4d;

	p4dp = (p4d_t *) pgdp;
	if ((pgd_val(pgd) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R1)
		p4dp = (p4d_t *) pgd_deref(pgd);
	p4dp += p4d_index(addr);
	do {
		p4d = *p4dp;
		barrier();
		next = p4d_addr_end(addr, end);
		if (p4d_none(p4d))
			return 0;
		if (!gup_pud_range(p4dp, p4d, addr, next, write, pages, nr))
			return 0;
	} while (p4dp++, addr = next, addr != end);

	return 1;
}
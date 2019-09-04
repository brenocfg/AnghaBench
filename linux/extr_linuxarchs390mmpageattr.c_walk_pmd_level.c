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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PMD_MASK ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  modify_pmd_page (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int split_pmd_page (int /*<<< orphan*/ *,unsigned long) ; 
 int walk_pte_level (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int walk_pmd_level(pud_t *pudp, unsigned long addr, unsigned long end,
			  unsigned long flags)
{
	unsigned long next;
	pmd_t *pmdp;
	int rc = 0;

	pmdp = pmd_offset(pudp, addr);
	do {
		if (pmd_none(*pmdp))
			return -EINVAL;
		next = pmd_addr_end(addr, end);
		if (pmd_large(*pmdp)) {
			if (addr & ~PMD_MASK || addr + PMD_SIZE > next) {
				rc = split_pmd_page(pmdp, addr);
				if (rc)
					return rc;
				continue;
			}
			modify_pmd_page(pmdp, addr, flags);
		} else {
			rc = walk_pte_level(pmdp, addr, next, flags);
			if (rc)
				return rc;
		}
		pmdp++;
		addr = next;
		cond_resched();
	} while (addr < end);
	return rc;
}
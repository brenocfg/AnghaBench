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
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int walk_pud_level (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int walk_p4d_level(pgd_t *pgd, unsigned long addr, unsigned long end,
			  unsigned long flags)
{
	unsigned long next;
	p4d_t *p4dp;
	int rc = 0;

	p4dp = p4d_offset(pgd, addr);
	do {
		if (p4d_none(*p4dp))
			return -EINVAL;
		next = p4d_addr_end(addr, end);
		rc = walk_pud_level(p4dp, addr, next, flags);
		p4dp++;
		addr = next;
		cond_resched();
	} while (addr < end && !rc);
	return rc;
}
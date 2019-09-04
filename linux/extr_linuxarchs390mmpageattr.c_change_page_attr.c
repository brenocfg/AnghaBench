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

/* Variables and functions */
 int EINVAL ; 
 unsigned long MODULES_END ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpa_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int walk_p4d_level (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int change_page_attr(unsigned long addr, unsigned long end,
			    unsigned long flags)
{
	unsigned long next;
	int rc = -EINVAL;
	pgd_t *pgdp;

	if (addr == end)
		return 0;
	if (end >= MODULES_END)
		return -EINVAL;
	mutex_lock(&cpa_mutex);
	pgdp = pgd_offset_k(addr);
	do {
		if (pgd_none(*pgdp))
			break;
		next = pgd_addr_end(addr, end);
		rc = walk_p4d_level(pgdp, addr, next, flags);
		if (rc)
			break;
		cond_resched();
	} while (pgdp++, addr = next, addr < end && !rc);
	mutex_unlock(&cpa_mutex);
	return rc;
}
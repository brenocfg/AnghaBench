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
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 unsigned long PMD_SIZE ; 
 unsigned long PUD_SIZE ; 
 int /*<<< orphan*/ * p4d_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 

pte_t *huge_pte_alloc(struct mm_struct *mm,
			unsigned long addr, unsigned long sz)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp = NULL;

	pgdp = pgd_offset(mm, addr);
	p4dp = p4d_alloc(mm, pgdp, addr);
	if (p4dp) {
		pudp = pud_alloc(mm, p4dp, addr);
		if (pudp) {
			if (sz == PUD_SIZE)
				return (pte_t *) pudp;
			else if (sz == PMD_SIZE)
				pmdp = pmd_alloc(mm, pudp, addr);
		}
	}
	return (pte_t *) pmdp;
}
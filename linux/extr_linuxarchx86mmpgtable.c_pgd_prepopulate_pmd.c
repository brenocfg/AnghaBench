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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int KERNEL_PGD_BOUNDARY ; 
 int PREALLOCATED_PMDS ; 
 int PTRS_PER_PMD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_page_vaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * swapper_pg_dir ; 

__attribute__((used)) static void pgd_prepopulate_pmd(struct mm_struct *mm, pgd_t *pgd, pmd_t *pmds[])
{
	p4d_t *p4d;
	pud_t *pud;
	int i;

	if (PREALLOCATED_PMDS == 0) /* Work around gcc-3.4.x bug */
		return;

	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);

	for (i = 0; i < PREALLOCATED_PMDS; i++, pud++) {
		pmd_t *pmd = pmds[i];

		if (i >= KERNEL_PGD_BOUNDARY)
			memcpy(pmd, (pmd_t *)pgd_page_vaddr(swapper_pg_dir[i]),
			       sizeof(pmd_t) * PTRS_PER_PMD);

		pud_populate(mm, pud, pmd);
	}
}
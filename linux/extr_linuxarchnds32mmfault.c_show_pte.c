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
struct mm_struct {int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HIGHMEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct mm_struct init_mm ; 
 scalar_t__ pgd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 

void show_pte(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	if (!mm)
		mm = &init_mm;

	pr_alert("pgd = %p\n", mm->pgd);
	pgd = pgd_offset(mm, addr);
	pr_alert("[%08lx] *pgd=%08lx", addr, pgd_val(*pgd));

	do {
		pmd_t *pmd;

		if (pgd_none(*pgd))
			break;

		if (pgd_bad(*pgd)) {
			pr_alert("(bad)");
			break;
		}

		pmd = pmd_offset(pgd, addr);
#if PTRS_PER_PMD != 1
		pr_alert(", *pmd=%08lx", pmd_val(*pmd));
#endif

		if (pmd_none(*pmd))
			break;

		if (pmd_bad(*pmd)) {
			pr_alert("(bad)");
			break;
		}

		if (IS_ENABLED(CONFIG_HIGHMEM))
		{
			pte_t *pte;
			/* We must not map this if we have highmem enabled */
			pte = pte_offset_map(pmd, addr);
			pr_alert(", *pte=%08lx", pte_val(*pte));
			pte_unmap(pte);
		}
	} while (0);

	pr_alert("\n");
}
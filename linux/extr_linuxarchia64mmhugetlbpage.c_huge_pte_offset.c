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

/* Variables and functions */
 unsigned long htlbpage_to_page (unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 scalar_t__ pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_present (int /*<<< orphan*/ ) ; 

pte_t *
huge_pte_offset (struct mm_struct *mm, unsigned long addr, unsigned long sz)
{
	unsigned long taddr = htlbpage_to_page(addr);
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = NULL;

	pgd = pgd_offset(mm, taddr);
	if (pgd_present(*pgd)) {
		pud = pud_offset(pgd, taddr);
		if (pud_present(*pud)) {
			pmd = pmd_offset(pud, taddr);
			if (pmd_present(*pmd))
				pte = pte_offset_map(pmd, taddr);
		}
	}

	return pte;
}
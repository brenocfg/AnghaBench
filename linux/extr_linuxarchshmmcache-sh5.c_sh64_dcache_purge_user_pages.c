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
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ pgd_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 scalar_t__ pmd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sh64_dcache_purge_coloured_phy_page (unsigned long,unsigned long) ; 

__attribute__((used)) static void sh64_dcache_purge_user_pages(struct mm_struct *mm,
				unsigned long addr, unsigned long end)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;
	spinlock_t *ptl;
	unsigned long paddr;

	if (!mm)
		return; /* No way to find physical address of page */

	pgd = pgd_offset(mm, addr);
	if (pgd_bad(*pgd))
		return;

	pud = pud_offset(pgd, addr);
	if (pud_none(*pud) || pud_bad(*pud))
		return;

	pmd = pmd_offset(pud, addr);
	if (pmd_none(*pmd) || pmd_bad(*pmd))
		return;

	pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
	do {
		entry = *pte;
		if (pte_none(entry) || !pte_present(entry))
			continue;
		paddr = pte_val(entry) & PAGE_MASK;
		sh64_dcache_purge_coloured_phy_page(paddr, addr);
	} while (pte++, addr += PAGE_SIZE, addr != end);
	pte_unmap_unlock(pte - 1, ptl);
}
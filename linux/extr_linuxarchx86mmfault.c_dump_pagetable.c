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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __va (int /*<<< orphan*/ ) ; 
 scalar_t__ bad_address (int /*<<< orphan*/ *) ; 
 scalar_t__ p4d_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4d_val (int /*<<< orphan*/ ) ; 
 int pgd_index (unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cr3_pa () ; 

__attribute__((used)) static void dump_pagetable(unsigned long address)
{
	pgd_t *base = __va(read_cr3_pa());
	pgd_t *pgd = base + pgd_index(address);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	if (bad_address(pgd))
		goto bad;

	pr_info("PGD %lx ", pgd_val(*pgd));

	if (!pgd_present(*pgd))
		goto out;

	p4d = p4d_offset(pgd, address);
	if (bad_address(p4d))
		goto bad;

	pr_cont("P4D %lx ", p4d_val(*p4d));
	if (!p4d_present(*p4d) || p4d_large(*p4d))
		goto out;

	pud = pud_offset(p4d, address);
	if (bad_address(pud))
		goto bad;

	pr_cont("PUD %lx ", pud_val(*pud));
	if (!pud_present(*pud) || pud_large(*pud))
		goto out;

	pmd = pmd_offset(pud, address);
	if (bad_address(pmd))
		goto bad;

	pr_cont("PMD %lx ", pmd_val(*pmd));
	if (!pmd_present(*pmd) || pmd_large(*pmd))
		goto out;

	pte = pte_offset_kernel(pmd, address);
	if (bad_address(pte))
		goto bad;

	pr_cont("PTE %lx", pte_val(*pte));
out:
	pr_cont("\n");
	return;
bad:
	pr_info("BAD\n");
}
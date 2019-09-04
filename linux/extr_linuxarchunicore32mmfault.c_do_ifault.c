#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;

/* Variables and functions */
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/ * cpu_get_pgd () ; 
 int /*<<< orphan*/  do_bad_area (unsigned long,unsigned int,struct pt_regs*) ; 
 int do_pf (unsigned long,unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  flush_pmd_entry (int /*<<< orphan*/ *) ; 
 TYPE_1__ init_mm ; 
 unsigned int pgd_index (unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int do_ifault(unsigned long addr, unsigned int fsr, struct pt_regs *regs)
{
	unsigned int index;
	pgd_t *pgd, *pgd_k;
	pmd_t *pmd, *pmd_k;

	if (addr < TASK_SIZE)
		return do_pf(addr, fsr, regs);

	if (user_mode(regs))
		goto bad_area;

	index = pgd_index(addr);

	pgd = cpu_get_pgd() + index;
	pgd_k = init_mm.pgd + index;

	if (pgd_none(*pgd_k))
		goto bad_area;

	pmd_k = pmd_offset((pud_t *) pgd_k, addr);
	pmd = pmd_offset((pud_t *) pgd, addr);

	if (pmd_none(*pmd_k))
		goto bad_area;

	set_pmd(pmd, *pmd_k);
	flush_pmd_entry(pmd);
	return 0;

bad_area:
	do_bad_area(addr, fsr, regs);
	return 0;
}
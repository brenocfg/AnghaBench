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
struct mm_struct {int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ULONG_MAX ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/ * find_current_mm_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_init_mm_pte (unsigned long,int /*<<< orphan*/ *) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_special (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static unsigned long addr_to_pfn(struct pt_regs *regs, unsigned long addr)
{
	pte_t *ptep;
	unsigned long flags;
	struct mm_struct *mm;

	if (user_mode(regs))
		mm = current->mm;
	else
		mm = &init_mm;

	local_irq_save(flags);
	if (mm == current->mm)
		ptep = find_current_mm_pte(mm->pgd, addr, NULL, NULL);
	else
		ptep = find_init_mm_pte(addr, NULL);
	local_irq_restore(flags);
	if (!ptep || pte_special(*ptep))
		return ULONG_MAX;
	return pte_pfn(*ptep);
}
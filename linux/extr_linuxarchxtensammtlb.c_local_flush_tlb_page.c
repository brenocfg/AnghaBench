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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct TYPE_2__ {scalar_t__* asid; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int ASID_INSERT (scalar_t__) ; 
 scalar_t__ NO_CONTEXT ; 
 int VM_EXEC ; 
 int get_rasid_register () ; 
 int /*<<< orphan*/  invalidate_dtlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  invalidate_itlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  set_rasid_register (int) ; 
 int smp_processor_id () ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	int cpu = smp_processor_id();
	struct mm_struct* mm = vma->vm_mm;
	unsigned long flags;
	int oldpid;

	if (mm->context.asid[cpu] == NO_CONTEXT)
		return;

	local_irq_save(flags);

	oldpid = get_rasid_register();
	set_rasid_register(ASID_INSERT(mm->context.asid[cpu]));

	if (vma->vm_flags & VM_EXEC)
		invalidate_itlb_mapping(page);
	invalidate_dtlb_mapping(page);

	set_rasid_register(oldpid);

	local_irq_restore(flags);
}
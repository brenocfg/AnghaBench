#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; int vm_flags; struct vm_area_struct* vm_next; } ;
struct mm_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSEGV ; 
 int VM_MPX ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kernel_managing_mpx_tables (int /*<<< orphan*/ ) ; 
 int mpx_unmap_tables (struct mm_struct*,unsigned long,unsigned long) ; 

void mpx_notify_unmap(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long start, unsigned long end)
{
	int ret;

	/*
	 * Refuse to do anything unless userspace has asked
	 * the kernel to help manage the bounds tables,
	 */
	if (!kernel_managing_mpx_tables(current->mm))
		return;
	/*
	 * This will look across the entire 'start -> end' range,
	 * and find all of the non-VM_MPX VMAs.
	 *
	 * To avoid recursion, if a VM_MPX vma is found in the range
	 * (start->end), we will not continue follow-up work. This
	 * recursion represents having bounds tables for bounds tables,
	 * which should not occur normally. Being strict about it here
	 * helps ensure that we do not have an exploitable stack overflow.
	 */
	do {
		if (vma->vm_flags & VM_MPX)
			return;
		vma = vma->vm_next;
	} while (vma && vma->vm_start < end);

	ret = mpx_unmap_tables(mm, start, end);
	if (ret)
		force_sig(SIGSEGV, current);
}
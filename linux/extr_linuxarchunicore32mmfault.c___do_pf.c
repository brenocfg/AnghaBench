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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  VM_FAULT_BADACCESS ; 
 int /*<<< orphan*/  VM_FAULT_BADMAP ; 
 int VM_GROWSDOWN ; 
 scalar_t__ access_error (unsigned int,struct vm_area_struct*) ; 
 int /*<<< orphan*/  expand_stack (struct vm_area_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static vm_fault_t __do_pf(struct mm_struct *mm, unsigned long addr,
		unsigned int fsr, unsigned int flags, struct task_struct *tsk)
{
	struct vm_area_struct *vma;
	vm_fault_t fault;

	vma = find_vma(mm, addr);
	fault = VM_FAULT_BADMAP;
	if (unlikely(!vma))
		goto out;
	if (unlikely(vma->vm_start > addr))
		goto check_stack;

	/*
	 * Ok, we have a good vm_area for this
	 * memory access, so we can handle it.
	 */
good_area:
	if (access_error(fsr, vma)) {
		fault = VM_FAULT_BADACCESS;
		goto out;
	}

	/*
	 * If for any reason at all we couldn't handle the fault, make
	 * sure we exit gracefully rather than endlessly redo the fault.
	 */
	fault = handle_mm_fault(vma, addr & PAGE_MASK, flags);
	return fault;

check_stack:
	if (vma->vm_flags & VM_GROWSDOWN && !expand_stack(vma, addr))
		goto good_area;
out:
	return fault;
}
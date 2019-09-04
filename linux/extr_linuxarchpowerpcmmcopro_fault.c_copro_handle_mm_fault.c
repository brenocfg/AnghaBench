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
typedef  int vm_fault_t ;
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/ * pgd; } ;
struct TYPE_2__ {int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long DSISR_ISSTORE ; 
 unsigned long DSISR_PROTFAULT ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 int VM_EXEC ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SIGBUS ; 
 int VM_FAULT_SIGSEGV ; 
 int VM_GROWSDOWN ; 
 int VM_READ ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_stack (struct vm_area_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int handle_mm_fault (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_enabled () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int copro_handle_mm_fault(struct mm_struct *mm, unsigned long ea,
		unsigned long dsisr, vm_fault_t *flt)
{
	struct vm_area_struct *vma;
	unsigned long is_write;
	int ret;

	if (mm == NULL)
		return -EFAULT;

	if (mm->pgd == NULL)
		return -EFAULT;

	down_read(&mm->mmap_sem);
	ret = -EFAULT;
	vma = find_vma(mm, ea);
	if (!vma)
		goto out_unlock;

	if (ea < vma->vm_start) {
		if (!(vma->vm_flags & VM_GROWSDOWN))
			goto out_unlock;
		if (expand_stack(vma, ea))
			goto out_unlock;
	}

	is_write = dsisr & DSISR_ISSTORE;
	if (is_write) {
		if (!(vma->vm_flags & VM_WRITE))
			goto out_unlock;
	} else {
		if (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			goto out_unlock;
		/*
		 * PROT_NONE is covered by the VMA check above.
		 * and hash should get a NOHPTE fault instead of
		 * a PROTFAULT in case fixup is needed for things
		 * like autonuma.
		 */
		if (!radix_enabled())
			WARN_ON_ONCE(dsisr & DSISR_PROTFAULT);
	}

	ret = 0;
	*flt = handle_mm_fault(vma, ea, is_write ? FAULT_FLAG_WRITE : 0);
	if (unlikely(*flt & VM_FAULT_ERROR)) {
		if (*flt & VM_FAULT_OOM) {
			ret = -ENOMEM;
			goto out_unlock;
		} else if (*flt & (VM_FAULT_SIGBUS | VM_FAULT_SIGSEGV)) {
			ret = -EFAULT;
			goto out_unlock;
		}
		BUG();
	}

	if (*flt & VM_FAULT_MAJOR)
		current->maj_flt++;
	else
		current->min_flt++;

out_unlock:
	up_read(&mm->mmap_sem);
	return ret;
}
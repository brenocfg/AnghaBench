#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * vdso; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; TYPE_1__ context; } ;
struct linux_binprm {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int PAGE_SHIFT ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 int VM_READ ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned long get_unmapped_area (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int install_special_mapping (struct mm_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdso_pagelist ; 
 int vdso_pages ; 

int arch_setup_additional_pages(struct linux_binprm *bprm,
	int uses_interp)
{
	struct mm_struct *mm = current->mm;
	unsigned long vdso_base, vdso_len;
	int ret;

	vdso_len = (vdso_pages + 1) << PAGE_SHIFT;

	down_write(&mm->mmap_sem);
	vdso_base = get_unmapped_area(NULL, 0, vdso_len, 0, 0);
	if (IS_ERR_VALUE(vdso_base)) {
		ret = vdso_base;
		goto end;
	}

	/*
	 * Put vDSO base into mm struct. We need to do this before calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO (since arch_vma_name fails).
	 */
	mm->context.vdso = (void *)vdso_base;

	ret = install_special_mapping(mm, vdso_base, vdso_len,
		(VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC),
		vdso_pagelist);

	if (unlikely(ret))
		mm->context.vdso = NULL;

end:
	up_write(&mm->mmap_sem);
	return ret;
}
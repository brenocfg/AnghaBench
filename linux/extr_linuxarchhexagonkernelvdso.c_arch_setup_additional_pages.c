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
struct TYPE_3__ {void* vdso; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; TYPE_1__ context; } ;
struct linux_binprm {int dummy; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long STACK_TOP ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 int VM_READ ; 
 TYPE_2__* current ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 unsigned long get_unmapped_area (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int install_special_mapping (struct mm_struct*,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdso_page ; 

int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
{
	int ret;
	unsigned long vdso_base;
	struct mm_struct *mm = current->mm;

	if (down_write_killable(&mm->mmap_sem))
		return -EINTR;

	/* Try to get it loaded right near ld.so/glibc. */
	vdso_base = STACK_TOP;

	vdso_base = get_unmapped_area(NULL, vdso_base, PAGE_SIZE, 0, 0);
	if (IS_ERR_VALUE(vdso_base)) {
		ret = vdso_base;
		goto up_fail;
	}

	/* MAYWRITE to allow gdb to COW and set breakpoints. */
	ret = install_special_mapping(mm, vdso_base, PAGE_SIZE,
				      VM_READ|VM_EXEC|
				      VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				      &vdso_page);

	if (ret)
		goto up_fail;

	mm->context.vdso = (void *)vdso_base;

up_fail:
	up_write(&mm->mmap_sem);
	return ret;
}
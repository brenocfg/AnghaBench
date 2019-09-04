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
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct linux_binprm {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KUSER_BASE ; 
 int /*<<< orphan*/  KUSER_SIZE ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_READ ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int install_special_mapping (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuser_page ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
{
	struct mm_struct *mm = current->mm;
	int ret;

	down_write(&mm->mmap_sem);

	/* Map kuser helpers to user space address */
	ret = install_special_mapping(mm, KUSER_BASE, KUSER_SIZE,
				      VM_READ | VM_EXEC | VM_MAYREAD |
				      VM_MAYEXEC, kuser_page);

	up_write(&mm->mmap_sem);

	return ret;
}
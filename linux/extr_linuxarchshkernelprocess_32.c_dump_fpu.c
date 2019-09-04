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
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  elf_fpregset_t ;

/* Variables and functions */

int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fpu)
{
	int fpvalid = 0;

#if defined(CONFIG_SH_FPU)
	struct task_struct *tsk = current;

	fpvalid = !!tsk_used_math(tsk);
	if (fpvalid)
		fpvalid = !fpregs_get(tsk, NULL, 0,
				      sizeof(struct user_fpu_struct),
				      fpu, NULL);
#endif

	return fpvalid;
}
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
#ifdef CONFIG_SH_FPU
	int fpvalid;
	struct task_struct *tsk = current;

	fpvalid = !!tsk_used_math(tsk);
	if (fpvalid) {
		if (current == last_task_used_math) {
			enable_fpu();
			save_fpu(tsk);
			disable_fpu();
			last_task_used_math = 0;
			regs->sr |= SR_FD;
		}

		memcpy(fpu, &tsk->thread.xstate->hardfpu, sizeof(*fpu));
	}

	return fpvalid;
#else
	return 0; /* Task didn't use the fpu at all. */
#endif
}
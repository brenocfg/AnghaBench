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

/* Variables and functions */

__attribute__((used)) static void __set_personality_ia32(void)
{
#ifdef CONFIG_IA32_EMULATION
	set_thread_flag(TIF_IA32);
	clear_thread_flag(TIF_X32);
	if (current->mm)
		current->mm->context.ia32_compat = TIF_IA32;
	current->personality |= force_personality32;
	/* Prepare the first "return" to user space */
	task_pt_regs(current)->orig_ax = __NR_ia32_execve;
	current_thread_info()->status |= TS_COMPAT;
#endif
}
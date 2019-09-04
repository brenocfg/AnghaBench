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
struct task_struct {int dummy; } ;

/* Variables and functions */
 unsigned long DEBUGCTLMSR_BTF ; 
 int /*<<< orphan*/  TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 unsigned long get_debugctlmsr () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_debugctlmsr (unsigned long) ; 

void set_task_blockstep(struct task_struct *task, bool on)
{
	unsigned long debugctl;

	/*
	 * Ensure irq/preemption can't change debugctl in between.
	 * Note also that both TIF_BLOCKSTEP and debugctl should
	 * be changed atomically wrt preemption.
	 *
	 * NOTE: this means that set/clear TIF_BLOCKSTEP is only safe if
	 * task is current or it can't be running, otherwise we can race
	 * with __switch_to_xtra(). We rely on ptrace_freeze_traced() but
	 * PTRACE_KILL is not safe.
	 */
	local_irq_disable();
	debugctl = get_debugctlmsr();
	if (on) {
		debugctl |= DEBUGCTLMSR_BTF;
		set_tsk_thread_flag(task, TIF_BLOCKSTEP);
	} else {
		debugctl &= ~DEBUGCTLMSR_BTF;
		clear_tsk_thread_flag(task, TIF_BLOCKSTEP);
	}
	if (task == current)
		update_debugctlmsr(debugctl);
	local_irq_enable();
}
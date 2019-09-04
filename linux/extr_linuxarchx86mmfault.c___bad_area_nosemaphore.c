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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long cr2; unsigned long error_code; int /*<<< orphan*/  trap_nr; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSEGV ; 
 unsigned long TASK_SIZE_MAX ; 
 unsigned long X86_PF_PROT ; 
 unsigned long X86_PF_USER ; 
 int /*<<< orphan*/  X86_TRAP_PF ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  force_sig_info_fault (int /*<<< orphan*/ ,int,unsigned long,struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_errata100 (struct pt_regs*,unsigned long) ; 
 scalar_t__ is_f00f_bug (struct pt_regs*,unsigned long) ; 
 scalar_t__ is_prefetch (struct pt_regs*,unsigned long,unsigned long) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  no_context (struct pt_regs*,unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  show_signal_msg (struct pt_regs*,unsigned long,unsigned long,struct task_struct*) ; 
 int /*<<< orphan*/  show_unhandled_signals ; 

__attribute__((used)) static void
__bad_area_nosemaphore(struct pt_regs *regs, unsigned long error_code,
		       unsigned long address, u32 *pkey, int si_code)
{
	struct task_struct *tsk = current;

	/* User mode accesses just cause a SIGSEGV */
	if (error_code & X86_PF_USER) {
		/*
		 * It's possible to have interrupts off here:
		 */
		local_irq_enable();

		/*
		 * Valid to do another page fault here because this one came
		 * from user space:
		 */
		if (is_prefetch(regs, error_code, address))
			return;

		if (is_errata100(regs, address))
			return;

#ifdef CONFIG_X86_64
		/*
		 * Instruction fetch faults in the vsyscall page might need
		 * emulation.
		 */
		if (unlikely((error_code & X86_PF_INSTR) &&
			     ((address & ~0xfff) == VSYSCALL_ADDR))) {
			if (emulate_vsyscall(regs, address))
				return;
		}
#endif

		/*
		 * To avoid leaking information about the kernel page table
		 * layout, pretend that user-mode accesses to kernel addresses
		 * are always protection faults.
		 */
		if (address >= TASK_SIZE_MAX)
			error_code |= X86_PF_PROT;

		if (likely(show_unhandled_signals))
			show_signal_msg(regs, error_code, address, tsk);

		tsk->thread.cr2		= address;
		tsk->thread.error_code	= error_code;
		tsk->thread.trap_nr	= X86_TRAP_PF;

		force_sig_info_fault(SIGSEGV, si_code, address, tsk, pkey, 0);

		return;
	}

	if (is_f00f_bug(regs, address))
		return;

	no_context(regs, error_code, address, SIGSEGV, si_code);
}
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
struct pt_regs {scalar_t__ tra; unsigned int* regs; scalar_t__ pc; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa; } ;
struct ksignal {TYPE_1__ ka; } ;

/* Variables and functions */
 unsigned int ERESTARTNOHAND ; 
 unsigned int ERESTARTNOINTR ; 
 unsigned int ERESTARTSYS ; 
 unsigned int ERESTART_RESTARTBLOCK ; 
 unsigned int __NR_restart_syscall ; 
 int /*<<< orphan*/  __raw_readw (scalar_t__) ; 
 scalar_t__ get_signal (struct ksignal*) ; 
 int /*<<< orphan*/  handle_signal (struct ksignal*,struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  handle_syscall_restart (unsigned int,struct pt_regs*,int /*<<< orphan*/ *) ; 
 scalar_t__ instruction_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_saved_sigmask () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static void do_signal(struct pt_regs *regs, unsigned int save_r0)
{
	struct ksignal ksig;

	/*
	 * We want the common case to go fast, which
	 * is why we may in certain cases get here from
	 * kernel mode. Just return without doing anything
	 * if so.
	 */
	if (!user_mode(regs))
		return;

	if (get_signal(&ksig)) {
		handle_syscall_restart(save_r0, regs, &ksig.ka.sa);

		/* Whee!  Actually deliver the signal.  */
		handle_signal(&ksig, regs, save_r0);
		return;
	}

	/* Did we come from a system call? */
	if (regs->tra >= 0) {
		/* Restart the system call - no handlers present */
		if (regs->regs[0] == -ERESTARTNOHAND ||
		    regs->regs[0] == -ERESTARTSYS ||
		    regs->regs[0] == -ERESTARTNOINTR) {
			regs->regs[0] = save_r0;
			regs->pc -= instruction_size(__raw_readw(regs->pc - 4));
		} else if (regs->regs[0] == -ERESTART_RESTARTBLOCK) {
			regs->pc -= instruction_size(__raw_readw(regs->pc - 4));
			regs->regs[3] = __NR_restart_syscall;
		}
	}

	/*
	 * If there's no signal to deliver, we just put the saved sigmask
	 * back.
	 */
	restore_saved_sigmask();
}
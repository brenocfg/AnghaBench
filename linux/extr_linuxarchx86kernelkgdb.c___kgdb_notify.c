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
struct die_args {int /*<<< orphan*/  signr; int /*<<< orphan*/  trapnr; struct pt_regs* regs; } ;

/* Variables and functions */
#define  DIE_DEBUG 128 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdb_cpu_doing_single_step ; 
 scalar_t__ kgdb_handle_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,struct pt_regs*) ; 
 int single_step_cont (struct pt_regs*,struct die_args*) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static int __kgdb_notify(struct die_args *args, unsigned long cmd)
{
	struct pt_regs *regs = args->regs;

	switch (cmd) {
	case DIE_DEBUG:
		if (atomic_read(&kgdb_cpu_doing_single_step) != -1) {
			if (user_mode(regs))
				return single_step_cont(regs, args);
			break;
		} else if (test_thread_flag(TIF_SINGLESTEP))
			/* This means a user thread is single stepping
			 * a system call which should be ignored
			 */
			return NOTIFY_DONE;
		/* fall through */
	default:
		if (user_mode(regs))
			return NOTIFY_DONE;
	}

	if (kgdb_handle_exception(args->trapnr, args->signr, cmd, regs))
		return NOTIFY_DONE;

	/* Must touch watchdog before return to normal operation */
	touch_nmi_watchdog();
	return NOTIFY_STOP;
}
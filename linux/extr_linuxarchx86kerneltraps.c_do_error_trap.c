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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_TRAP ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  RCU_LOCKDEP_WARN (int,char*) ; 
 int /*<<< orphan*/  clear_siginfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_local_irq_enable (struct pt_regs*) ; 
 int /*<<< orphan*/  do_trap (unsigned long,int,char*,struct pt_regs*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_trap_info (struct pt_regs*,int,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ fixup_bug (struct pt_regs*,unsigned long) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char*,struct pt_regs*,long,unsigned long,int) ; 
 int /*<<< orphan*/  rcu_is_watching () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static void do_error_trap(struct pt_regs *regs, long error_code, char *str,
			  unsigned long trapnr, int signr)
{
	siginfo_t info;

	RCU_LOCKDEP_WARN(!rcu_is_watching(), "entry code didn't wake RCU");

	/*
	 * WARN*()s end up here; fix them up before we call the
	 * notifier chain.
	 */
	if (!user_mode(regs) && fixup_bug(regs, trapnr))
		return;

	if (notify_die(DIE_TRAP, str, regs, error_code, trapnr, signr) !=
			NOTIFY_STOP) {
		cond_local_irq_enable(regs);
		clear_siginfo(&info);
		do_trap(trapnr, signr, str, regs, error_code,
			fill_trap_info(regs, signr, trapnr, &info));
	}
}
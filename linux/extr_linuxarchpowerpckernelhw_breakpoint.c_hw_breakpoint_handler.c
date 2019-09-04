#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long dar; scalar_t__ nip; int /*<<< orphan*/  msr; } ;
struct TYPE_4__ {unsigned long bp_addr; unsigned long bp_len; } ;
struct perf_event {scalar_t__ overflow_handler; TYPE_1__ attr; } ;
struct die_args {struct pt_regs* regs; } ;
struct arch_hw_breakpoint {int type; int /*<<< orphan*/  address; } ;
struct TYPE_5__ {struct perf_event* last_hit_ubp; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int HW_BRK_TYPE_EXTRANEOUS_IRQ ; 
 int /*<<< orphan*/  MSR_SE ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_user_inatomic (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  __set_breakpoint (struct arch_hw_breakpoint*) ; 
 struct perf_event* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp_per_reg ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 TYPE_3__* current ; 
 int emulate_step (struct pt_regs*,unsigned int) ; 
 int /*<<< orphan*/  hw_breakpoint_disable () ; 
 int /*<<< orphan*/  perf_bp_event (struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_event_disable_inatomic (struct perf_event*) ; 
 scalar_t__ ptrace_triggered ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int hw_breakpoint_handler(struct die_args *args)
{
	int rc = NOTIFY_STOP;
	struct perf_event *bp;
	struct pt_regs *regs = args->regs;
#ifndef CONFIG_PPC_8xx
	int stepped = 1;
	unsigned int instr;
#endif
	struct arch_hw_breakpoint *info;
	unsigned long dar = regs->dar;

	/* Disable breakpoints during exception handling */
	hw_breakpoint_disable();

	/*
	 * The counter may be concurrently released but that can only
	 * occur from a call_rcu() path. We can then safely fetch
	 * the breakpoint, use its callback, touch its counter
	 * while we are in an rcu_read_lock() path.
	 */
	rcu_read_lock();

	bp = __this_cpu_read(bp_per_reg);
	if (!bp) {
		rc = NOTIFY_DONE;
		goto out;
	}
	info = counter_arch_bp(bp);

	/*
	 * Return early after invoking user-callback function without restoring
	 * DABR if the breakpoint is from ptrace which always operates in
	 * one-shot mode. The ptrace-ed process will receive the SIGTRAP signal
	 * generated in do_dabr().
	 */
	if (bp->overflow_handler == ptrace_triggered) {
		perf_bp_event(bp, regs);
		rc = NOTIFY_DONE;
		goto out;
	}

	/*
	 * Verify if dar lies within the address range occupied by the symbol
	 * being watched to filter extraneous exceptions.  If it doesn't,
	 * we still need to single-step the instruction, but we don't
	 * generate an event.
	 */
	info->type &= ~HW_BRK_TYPE_EXTRANEOUS_IRQ;
	if (!((bp->attr.bp_addr <= dar) &&
	      (dar - bp->attr.bp_addr < bp->attr.bp_len)))
		info->type |= HW_BRK_TYPE_EXTRANEOUS_IRQ;

#ifndef CONFIG_PPC_8xx
	/* Do not emulate user-space instructions, instead single-step them */
	if (user_mode(regs)) {
		current->thread.last_hit_ubp = bp;
		regs->msr |= MSR_SE;
		goto out;
	}

	stepped = 0;
	instr = 0;
	if (!__get_user_inatomic(instr, (unsigned int *) regs->nip))
		stepped = emulate_step(regs, instr);

	/*
	 * emulate_step() could not execute it. We've failed in reliably
	 * handling the hw-breakpoint. Unregister it and throw a warning
	 * message to let the user know about it.
	 */
	if (!stepped) {
		WARN(1, "Unable to handle hardware breakpoint. Breakpoint at "
			"0x%lx will be disabled.", info->address);
		perf_event_disable_inatomic(bp);
		goto out;
	}
#endif
	/*
	 * As a policy, the callback is invoked in a 'trigger-after-execute'
	 * fashion
	 */
	if (!(info->type & HW_BRK_TYPE_EXTRANEOUS_IRQ))
		perf_bp_event(bp, regs);

	__set_breakpoint(info);
out:
	rcu_read_unlock();
	return rc;
}
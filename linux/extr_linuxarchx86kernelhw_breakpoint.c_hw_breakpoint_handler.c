#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_1__ info; } ;
struct perf_event {TYPE_2__ hw; } ;
struct die_args {TYPE_4__* regs; int /*<<< orphan*/  err; } ;
struct TYPE_8__ {unsigned long debugreg6; } ;
struct TYPE_10__ {TYPE_3__ thread; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned long DR_STEP ; 
 int DR_TRAP0 ; 
 unsigned long DR_TRAP_BITS ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int HBP_NUM ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ X86_BREAKPOINT_EXECUTE ; 
 int /*<<< orphan*/  X86_EFLAGS_RF ; 
 int /*<<< orphan*/ * bp_per_reg ; 
 TYPE_5__* current ; 
 int get_cpu () ; 
 int /*<<< orphan*/  get_debugreg (unsigned long,int) ; 
 scalar_t__ likely (int) ; 
 struct perf_event* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_bp_event (struct perf_event*,TYPE_4__*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_debugreg (unsigned long,int) ; 

__attribute__((used)) static int hw_breakpoint_handler(struct die_args *args)
{
	int i, cpu, rc = NOTIFY_STOP;
	struct perf_event *bp;
	unsigned long dr7, dr6;
	unsigned long *dr6_p;

	/* The DR6 value is pointed by args->err */
	dr6_p = (unsigned long *)ERR_PTR(args->err);
	dr6 = *dr6_p;

	/* If it's a single step, TRAP bits are random */
	if (dr6 & DR_STEP)
		return NOTIFY_DONE;

	/* Do an early return if no trap bits are set in DR6 */
	if ((dr6 & DR_TRAP_BITS) == 0)
		return NOTIFY_DONE;

	get_debugreg(dr7, 7);
	/* Disable breakpoints during exception handling */
	set_debugreg(0UL, 7);
	/*
	 * Assert that local interrupts are disabled
	 * Reset the DRn bits in the virtualized register value.
	 * The ptrace trigger routine will add in whatever is needed.
	 */
	current->thread.debugreg6 &= ~DR_TRAP_BITS;
	cpu = get_cpu();

	/* Handle all the breakpoints that were triggered */
	for (i = 0; i < HBP_NUM; ++i) {
		if (likely(!(dr6 & (DR_TRAP0 << i))))
			continue;

		/*
		 * The counter may be concurrently released but that can only
		 * occur from a call_rcu() path. We can then safely fetch
		 * the breakpoint, use its callback, touch its counter
		 * while we are in an rcu_read_lock() path.
		 */
		rcu_read_lock();

		bp = per_cpu(bp_per_reg[i], cpu);
		/*
		 * Reset the 'i'th TRAP bit in dr6 to denote completion of
		 * exception handling
		 */
		(*dr6_p) &= ~(DR_TRAP0 << i);
		/*
		 * bp can be NULL due to lazy debug register switching
		 * or due to concurrent perf counter removing.
		 */
		if (!bp) {
			rcu_read_unlock();
			break;
		}

		perf_bp_event(bp, args->regs);

		/*
		 * Set up resume flag to avoid breakpoint recursion when
		 * returning back to origin.
		 */
		if (bp->hw.info.type == X86_BREAKPOINT_EXECUTE)
			args->regs->flags |= X86_EFLAGS_RF;

		rcu_read_unlock();
	}
	/*
	 * Further processing in do_debug() is needed for a) user-space
	 * breakpoints (to generate signals) and b) when the system has
	 * taken exception due to multiple causes
	 */
	if ((current->thread.debugreg6 & DR_TRAP_BITS) ||
	    (dr6 & (~DR_TRAP_BITS)))
		rc = NOTIFY_DONE;

	set_debugreg(dr7, 7);
	put_cpu();

	return rc;
}
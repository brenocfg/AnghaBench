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
struct pt_regs {int dummy; } ;
struct fpustate {int dummy; } ;
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;
struct TYPE_2__ {int* xfsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_TRAP ; 
 struct fpustate* FPUSTATE ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGFPE ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  do_fpe_common (struct pt_regs*) ; 
 int do_mathemu (struct pt_regs*,struct fpustate*,int) ; 
 int exception_enter () ; 
 int /*<<< orphan*/  exception_exit (int) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char*,struct pt_regs*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void do_fpother(struct pt_regs *regs)
{
	enum ctx_state prev_state = exception_enter();
	struct fpustate *f = FPUSTATE;
	int ret = 0;

	if (notify_die(DIE_TRAP, "fpu exception other", regs,
		       0, 0x25, SIGFPE) == NOTIFY_STOP)
		goto out;

	switch ((current_thread_info()->xfsr[0] & 0x1c000)) {
	case (2 << 14): /* unfinished_FPop */
	case (3 << 14): /* unimplemented_FPop */
		ret = do_mathemu(regs, f, false);
		break;
	}
	if (ret)
		goto out;
	do_fpe_common(regs);
out:
	exception_exit(prev_state);
}
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
typedef  int u64 ;
struct TYPE_5__ {int reg; } ;
struct TYPE_6__ {TYPE_2__ branch_reg; } ;
struct TYPE_4__ {int branch_sample_type; } ;
struct perf_event {TYPE_3__ hw; TYPE_1__ attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PERF_SAMPLE_BRANCH_ABORT_TX ; 
 int PERF_SAMPLE_BRANCH_ANY ; 
 int PERF_SAMPLE_BRANCH_ANY_CALL ; 
 int PERF_SAMPLE_BRANCH_ANY_RETURN ; 
 int PERF_SAMPLE_BRANCH_CALL ; 
 int PERF_SAMPLE_BRANCH_CALL_STACK ; 
 int PERF_SAMPLE_BRANCH_COND ; 
 int PERF_SAMPLE_BRANCH_IND_CALL ; 
 int PERF_SAMPLE_BRANCH_IND_JUMP ; 
 int PERF_SAMPLE_BRANCH_IN_TX ; 
 int PERF_SAMPLE_BRANCH_KERNEL ; 
 int PERF_SAMPLE_BRANCH_NO_TX ; 
 int PERF_SAMPLE_BRANCH_TYPE_SAVE ; 
 int PERF_SAMPLE_BRANCH_USER ; 
 int X86_BR_ABORT ; 
 int X86_BR_ANY ; 
 int X86_BR_ANY_CALL ; 
 int X86_BR_CALL ; 
 int X86_BR_CALL_STACK ; 
 int X86_BR_IND_CALL ; 
 int X86_BR_IND_JMP ; 
 int X86_BR_IN_TX ; 
 int X86_BR_IRET ; 
 int X86_BR_JCC ; 
 int X86_BR_KERNEL ; 
 int X86_BR_NO_TX ; 
 int X86_BR_RET ; 
 int X86_BR_SYSRET ; 
 int X86_BR_TYPE_SAVE ; 
 int X86_BR_USER ; 
 int X86_BR_ZERO_CALL ; 
 int /*<<< orphan*/  x86_pmu_has_lbr_callstack () ; 

__attribute__((used)) static int intel_pmu_setup_sw_lbr_filter(struct perf_event *event)
{
	u64 br_type = event->attr.branch_sample_type;
	int mask = 0;

	if (br_type & PERF_SAMPLE_BRANCH_USER)
		mask |= X86_BR_USER;

	if (br_type & PERF_SAMPLE_BRANCH_KERNEL)
		mask |= X86_BR_KERNEL;

	/* we ignore BRANCH_HV here */

	if (br_type & PERF_SAMPLE_BRANCH_ANY)
		mask |= X86_BR_ANY;

	if (br_type & PERF_SAMPLE_BRANCH_ANY_CALL)
		mask |= X86_BR_ANY_CALL;

	if (br_type & PERF_SAMPLE_BRANCH_ANY_RETURN)
		mask |= X86_BR_RET | X86_BR_IRET | X86_BR_SYSRET;

	if (br_type & PERF_SAMPLE_BRANCH_IND_CALL)
		mask |= X86_BR_IND_CALL;

	if (br_type & PERF_SAMPLE_BRANCH_ABORT_TX)
		mask |= X86_BR_ABORT;

	if (br_type & PERF_SAMPLE_BRANCH_IN_TX)
		mask |= X86_BR_IN_TX;

	if (br_type & PERF_SAMPLE_BRANCH_NO_TX)
		mask |= X86_BR_NO_TX;

	if (br_type & PERF_SAMPLE_BRANCH_COND)
		mask |= X86_BR_JCC;

	if (br_type & PERF_SAMPLE_BRANCH_CALL_STACK) {
		if (!x86_pmu_has_lbr_callstack())
			return -EOPNOTSUPP;
		if (mask & ~(X86_BR_USER | X86_BR_KERNEL))
			return -EINVAL;
		mask |= X86_BR_CALL | X86_BR_IND_CALL | X86_BR_RET |
			X86_BR_CALL_STACK;
	}

	if (br_type & PERF_SAMPLE_BRANCH_IND_JUMP)
		mask |= X86_BR_IND_JMP;

	if (br_type & PERF_SAMPLE_BRANCH_CALL)
		mask |= X86_BR_CALL | X86_BR_ZERO_CALL;

	if (br_type & PERF_SAMPLE_BRANCH_TYPE_SAVE)
		mask |= X86_BR_TYPE_SAVE;

	/*
	 * stash actual user request into reg, it may
	 * be used by fixup code for some CPU
	 */
	event->hw.branch_reg.reg = mask;
	return 0;
}
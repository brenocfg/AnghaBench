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
struct perf_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCHAL_NUM_DBREAK ; 
 int /*<<< orphan*/  XCHAL_NUM_IBREAK ; 
 scalar_t__ XTENSA_BREAKPOINT_EXECUTE ; 
 int alloc_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  bp_on_reg ; 
 TYPE_1__* counter_arch_bp (struct perf_event*) ; 
 int /*<<< orphan*/  set_dbreak_regs (int,struct perf_event*) ; 
 int /*<<< orphan*/  set_ibreak_regs (int,struct perf_event*) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 

int arch_install_hw_breakpoint(struct perf_event *bp)
{
	int i;

	if (counter_arch_bp(bp)->type == XTENSA_BREAKPOINT_EXECUTE) {
		/* Breakpoint */
		i = alloc_slot(this_cpu_ptr(bp_on_reg), XCHAL_NUM_IBREAK, bp);
		if (i < 0)
			return i;
		set_ibreak_regs(i, bp);

	} else {
		/* Watchpoint */
		i = alloc_slot(this_cpu_ptr(wp_on_reg), XCHAL_NUM_DBREAK, bp);
		if (i < 0)
			return i;
		set_dbreak_regs(i, bp);
	}
	return 0;
}
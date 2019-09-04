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
struct arch_hw_breakpoint {int dummy; } ;
struct TYPE_2__ {int num_events; int /*<<< orphan*/  clk; int /*<<< orphan*/  (* disable ) (struct arch_hw_breakpoint*,int) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/ * bp_per_reg ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 TYPE_1__* sh_ubc ; 
 int /*<<< orphan*/  stub1 (struct arch_hw_breakpoint*,int) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ *) ; 

void arch_uninstall_hw_breakpoint(struct perf_event *bp)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	int i;

	for (i = 0; i < sh_ubc->num_events; i++) {
		struct perf_event **slot = this_cpu_ptr(&bp_per_reg[i]);

		if (*slot == bp) {
			*slot = NULL;
			break;
		}
	}

	if (WARN_ONCE(i == sh_ubc->num_events, "Can't find any breakpoint slot"))
		return;

	sh_ubc->disable(info, i);
	clk_disable(sh_ubc->clk);
}
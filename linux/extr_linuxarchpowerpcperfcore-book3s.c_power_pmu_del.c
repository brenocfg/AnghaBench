#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ idx; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_1__ hw; } ;
struct cpu_hw_events {long n_events; int* mmcr; long n_limited; int /*<<< orphan*/ * limited_hwidx; struct perf_event** limited_counter; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * events; struct perf_event** event; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_pmc ) (scalar_t__,int*) ;} ;

/* Variables and functions */
 int MMCR0_FCECE ; 
 int MMCR0_PMXE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_pmu_bhrb_disable (struct perf_event*) ; 
 int /*<<< orphan*/  power_pmu_read (struct perf_event*) ; 
 TYPE_2__* ppmu ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pmc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void power_pmu_del(struct perf_event *event, int ef_flags)
{
	struct cpu_hw_events *cpuhw;
	long i;
	unsigned long flags;

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	power_pmu_read(event);

	cpuhw = this_cpu_ptr(&cpu_hw_events);
	for (i = 0; i < cpuhw->n_events; ++i) {
		if (event == cpuhw->event[i]) {
			while (++i < cpuhw->n_events) {
				cpuhw->event[i-1] = cpuhw->event[i];
				cpuhw->events[i-1] = cpuhw->events[i];
				cpuhw->flags[i-1] = cpuhw->flags[i];
			}
			--cpuhw->n_events;
			ppmu->disable_pmc(event->hw.idx - 1, cpuhw->mmcr);
			if (event->hw.idx) {
				write_pmc(event->hw.idx, 0);
				event->hw.idx = 0;
			}
			perf_event_update_userpage(event);
			break;
		}
	}
	for (i = 0; i < cpuhw->n_limited; ++i)
		if (event == cpuhw->limited_counter[i])
			break;
	if (i < cpuhw->n_limited) {
		while (++i < cpuhw->n_limited) {
			cpuhw->limited_counter[i-1] = cpuhw->limited_counter[i];
			cpuhw->limited_hwidx[i-1] = cpuhw->limited_hwidx[i];
		}
		--cpuhw->n_limited;
	}
	if (cpuhw->n_events == 0) {
		/* disable exceptions if no events are running */
		cpuhw->mmcr[0] &= ~(MMCR0_PMXE | MMCR0_FCECE);
	}

	if (has_branch_stack(event))
		power_pmu_bhrb_disable(event);

	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
}
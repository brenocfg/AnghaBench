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
struct TYPE_5__ {int /*<<< orphan*/  branch_sample_type; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  config; int /*<<< orphan*/  event_base; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_2__ attr; TYPE_1__ hw; } ;
struct cpu_hw_events {int n_events; int txn_flags; int /*<<< orphan*/  bhrb_filter; int /*<<< orphan*/  n_added; int /*<<< orphan*/ * events; int /*<<< orphan*/ * flags; struct perf_event** event; } ;
struct TYPE_6__ {int n_counter; int /*<<< orphan*/  (* bhrb_filter_map ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int PERF_PMU_TXN_ADD ; 
 scalar_t__ check_excludes (struct perf_event**,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  ebb_event_add (struct perf_event*) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ power_check_constraints (struct cpu_hw_events*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  power_pmu_bhrb_enable (struct perf_event*) ; 
 TYPE_3__* ppmu ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int power_pmu_add(struct perf_event *event, int ef_flags)
{
	struct cpu_hw_events *cpuhw;
	unsigned long flags;
	int n0;
	int ret = -EAGAIN;

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	/*
	 * Add the event to the list (if there is room)
	 * and check whether the total set is still feasible.
	 */
	cpuhw = this_cpu_ptr(&cpu_hw_events);
	n0 = cpuhw->n_events;
	if (n0 >= ppmu->n_counter)
		goto out;
	cpuhw->event[n0] = event;
	cpuhw->events[n0] = event->hw.config;
	cpuhw->flags[n0] = event->hw.event_base;

	/*
	 * This event may have been disabled/stopped in record_and_restart()
	 * because we exceeded the ->event_limit. If re-starting the event,
	 * clear the ->hw.state (STOPPED and UPTODATE flags), so the user
	 * notification is re-enabled.
	 */
	if (!(ef_flags & PERF_EF_START))
		event->hw.state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	else
		event->hw.state = 0;

	/*
	 * If group events scheduling transaction was started,
	 * skip the schedulability test here, it will be performed
	 * at commit time(->commit_txn) as a whole
	 */
	if (cpuhw->txn_flags & PERF_PMU_TXN_ADD)
		goto nocheck;

	if (check_excludes(cpuhw->event, cpuhw->flags, n0, 1))
		goto out;
	if (power_check_constraints(cpuhw, cpuhw->events, cpuhw->flags, n0 + 1))
		goto out;
	event->hw.config = cpuhw->events[n0];

nocheck:
	ebb_event_add(event);

	++cpuhw->n_events;
	++cpuhw->n_added;

	ret = 0;
 out:
	if (has_branch_stack(event)) {
		power_pmu_bhrb_enable(event);
		cpuhw->bhrb_filter = ppmu->bhrb_filter_map(
					event->attr.branch_sample_type);
	}

	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
	return ret;
}
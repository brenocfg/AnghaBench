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
struct TYPE_2__ {int state; scalar_t__ idx; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  pmu; } ;
struct dsu_pmu {int dummy; } ;

/* Variables and functions */
 scalar_t__ DSU_PMU_IDX_CYCLE_COUNTER ; 
 int PERF_EF_RELOAD ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsu_pmu_enable_counter (struct dsu_pmu*,scalar_t__) ; 
 int /*<<< orphan*/  dsu_pmu_set_event (struct dsu_pmu*,struct perf_event*) ; 
 int /*<<< orphan*/  dsu_pmu_set_event_period (struct perf_event*) ; 
 struct dsu_pmu* to_dsu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsu_pmu_start(struct perf_event *event, int pmu_flags)
{
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	/* We always reprogram the counter */
	if (pmu_flags & PERF_EF_RELOAD)
		WARN_ON(!(event->hw.state & PERF_HES_UPTODATE));
	dsu_pmu_set_event_period(event);
	if (event->hw.idx != DSU_PMU_IDX_CYCLE_COUNTER)
		dsu_pmu_set_event(dsu_pmu, event);
	event->hw.state = 0;
	dsu_pmu_enable_counter(dsu_pmu, event->hw.idx);
}
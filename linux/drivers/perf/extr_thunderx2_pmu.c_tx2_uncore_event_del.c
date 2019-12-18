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
struct tx2_uncore_pmu {int /*<<< orphan*/ ** events; } ;
struct hw_perf_event {size_t idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_COUNTERID (struct perf_event*) ; 
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  free_counter (struct tx2_uncore_pmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct tx2_uncore_pmu* pmu_to_tx2_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx2_uncore_event_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx2_uncore_event_del(struct perf_event *event, int flags)
{
	struct tx2_uncore_pmu *tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	tx2_uncore_event_stop(event, PERF_EF_UPDATE);

	/* clear the assigned counter */
	free_counter(tx2_pmu, GET_COUNTERID(event));

	perf_event_update_userpage(event);
	tx2_pmu->events[hwc->idx] = NULL;
	hwc->idx = -1;
}
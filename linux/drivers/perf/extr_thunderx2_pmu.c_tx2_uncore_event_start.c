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
struct tx2_uncore_pmu {int /*<<< orphan*/  hrtimer_interval; int /*<<< orphan*/  hrtimer; int /*<<< orphan*/  max_counters; int /*<<< orphan*/  active_counters; int /*<<< orphan*/  (* start_event ) (struct perf_event*,int) ;} ;
struct hw_perf_event {scalar_t__ state; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct tx2_uncore_pmu* pmu_to_tx2_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int) ; 

__attribute__((used)) static void tx2_uncore_event_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	struct tx2_uncore_pmu *tx2_pmu;

	hwc->state = 0;
	tx2_pmu = pmu_to_tx2_pmu(event->pmu);

	tx2_pmu->start_event(event, flags);
	perf_event_update_userpage(event);

	/* Start timer for first event */
	if (bitmap_weight(tx2_pmu->active_counters,
				tx2_pmu->max_counters) == 1) {
		hrtimer_start(&tx2_pmu->hrtimer,
			ns_to_ktime(tx2_pmu->hrtimer_interval),
			HRTIMER_MODE_REL_PINNED);
	}
}
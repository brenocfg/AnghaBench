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
struct tx2_uncore_pmu {int /*<<< orphan*/  (* stop_event ) (struct perf_event*) ;} ;
struct hw_perf_event {int state; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct tx2_uncore_pmu* pmu_to_tx2_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  tx2_uncore_event_update (struct perf_event*) ; 

__attribute__((used)) static void tx2_uncore_event_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	struct tx2_uncore_pmu *tx2_pmu;

	if (hwc->state & PERF_HES_UPTODATE)
		return;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	tx2_pmu->stop_event(event);
	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;
	if (flags & PERF_EF_UPDATE) {
		tx2_uncore_event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	}
}
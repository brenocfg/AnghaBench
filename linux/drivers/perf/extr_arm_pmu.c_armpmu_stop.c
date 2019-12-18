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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int /*<<< orphan*/  (* disable ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  armpmu_event_update (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
armpmu_stop(struct perf_event *event, int flags)
{
	struct arm_pmu *armpmu = to_arm_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	/*
	 * ARM pmu always has to update the counter, so ignore
	 * PERF_EF_UPDATE, see comments in armpmu_start().
	 */
	if (!(hwc->state & PERF_HES_STOPPED)) {
		armpmu->disable(event);
		armpmu_event_update(event);
		hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	}
}
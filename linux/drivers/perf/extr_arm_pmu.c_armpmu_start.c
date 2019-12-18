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
struct arm_pmu {int /*<<< orphan*/  (* enable ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  armpmu_event_set_period (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armpmu_start(struct perf_event *event, int flags)
{
	struct arm_pmu *armpmu = to_arm_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	/*
	 * ARM pmu always has to reprogram the period, so ignore
	 * PERF_EF_RELOAD, see the comment below.
	 */
	if (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;
	/*
	 * Set the period again. Some counters can't be stopped, so when we
	 * were stopped we simply disabled the IRQ source and the counter
	 * may have been left counting. If we don't do this step then we may
	 * get an interrupt too soon or *way* too late if the overflow has
	 * happened since disabling.
	 */
	armpmu_event_set_period(event);
	armpmu->enable(event);
}
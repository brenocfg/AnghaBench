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
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  cluster_pmu_counter_disable (int) ; 
 int /*<<< orphan*/  cluster_pmu_counter_disable_interrupt (int) ; 
 int /*<<< orphan*/  l2_cache_event_update (struct perf_event*) ; 

__attribute__((used)) static void l2_cache_event_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (hwc->state & PERF_HES_STOPPED)
		return;

	cluster_pmu_counter_disable_interrupt(idx);
	cluster_pmu_counter_disable(idx);

	if (flags & PERF_EF_UPDATE)
		l2_cache_event_update(event);
	hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
}
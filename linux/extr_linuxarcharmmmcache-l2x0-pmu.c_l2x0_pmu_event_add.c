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
 int EAGAIN ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 struct perf_event** events ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_pmu_event_configure (struct perf_event*) ; 
 int /*<<< orphan*/  l2x0_pmu_event_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int l2x0_pmu_find_idx () ; 
 int /*<<< orphan*/  l2x0_pmu_hrtimer ; 
 scalar_t__ l2x0_pmu_num_active_counters () ; 
 int /*<<< orphan*/  l2x0_pmu_poll_period ; 

__attribute__((used)) static int l2x0_pmu_event_add(struct perf_event *event, int flags)
{
	struct hw_perf_event *hw = &event->hw;
	int idx = l2x0_pmu_find_idx();

	if (idx == -1)
		return -EAGAIN;

	/*
	 * Pin the timer, so that the overflows are handled by the chosen
	 * event->cpu (this is the same one as presented in "cpumask"
	 * attribute).
	 */
	if (l2x0_pmu_num_active_counters() == 0)
		hrtimer_start(&l2x0_pmu_hrtimer, l2x0_pmu_poll_period,
			      HRTIMER_MODE_REL_PINNED);

	events[idx] = event;
	hw->idx = idx;

	l2x0_pmu_event_configure(event);

	hw->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;

	if (flags & PERF_EF_START)
		l2x0_pmu_event_start(event, 0);

	return 0;
}
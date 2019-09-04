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
struct perf_event {int dummy; } ;
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_RESTART ; 
 int PMU_NR_COUNTERS ; 
 int /*<<< orphan*/  __l2x0_pmu_disable () ; 
 int /*<<< orphan*/  __l2x0_pmu_enable () ; 
 struct perf_event** events ; 
 int /*<<< orphan*/  hrtimer_forward_now (struct hrtimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_pmu_event_configure (struct perf_event*) ; 
 int /*<<< orphan*/  l2x0_pmu_event_read (struct perf_event*) ; 
 int /*<<< orphan*/  l2x0_pmu_poll_period ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static enum hrtimer_restart l2x0_pmu_poll(struct hrtimer *hrtimer)
{
	unsigned long flags;
	int i;

	local_irq_save(flags);
	__l2x0_pmu_disable();

	for (i = 0; i < PMU_NR_COUNTERS; i++) {
		struct perf_event *event = events[i];

		if (!event)
			continue;

		l2x0_pmu_event_read(event);
		l2x0_pmu_event_configure(event);
	}

	__l2x0_pmu_enable();
	local_irq_restore(flags);

	hrtimer_forward_now(hrtimer, l2x0_pmu_poll_period);
	return HRTIMER_RESTART;
}
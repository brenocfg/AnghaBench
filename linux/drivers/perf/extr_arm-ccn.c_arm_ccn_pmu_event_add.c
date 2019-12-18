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
struct hw_perf_event {int /*<<< orphan*/  state; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  hrtimer; } ;
struct arm_ccn {TYPE_1__ dt; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int PERF_EF_START ; 
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  PERF_HES_STOPPED ; 
 int arm_ccn_pmu_active_counters (struct arm_ccn*) ; 
 int arm_ccn_pmu_event_alloc (struct perf_event*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_event_config (struct perf_event*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_event_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_ccn_pmu_timer_period () ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_ccn_pmu_event_add(struct perf_event *event, int flags)
{
	int err;
	struct hw_perf_event *hw = &event->hw;
	struct arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);

	err = arm_ccn_pmu_event_alloc(event);
	if (err)
		return err;

	/*
	 * Pin the timer, so that the overflows are handled by the chosen
	 * event->cpu (this is the same one as presented in "cpumask"
	 * attribute).
	 */
	if (!ccn->irq && arm_ccn_pmu_active_counters(ccn) == 1)
		hrtimer_start(&ccn->dt.hrtimer, arm_ccn_pmu_timer_period(),
			      HRTIMER_MODE_REL_PINNED);

	arm_ccn_pmu_event_config(event);

	hw->state = PERF_HES_STOPPED;

	if (flags & PERF_EF_START)
		arm_ccn_pmu_event_start(event, PERF_EF_UPDATE);

	return 0;
}
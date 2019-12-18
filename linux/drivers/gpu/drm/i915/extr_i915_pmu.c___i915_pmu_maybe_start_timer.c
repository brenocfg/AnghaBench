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
struct i915_pmu {int timer_enabled; int /*<<< orphan*/  timer; int /*<<< orphan*/  timer_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  PERIOD ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 scalar_t__ pmu_needs_timer (struct i915_pmu*,int) ; 

__attribute__((used)) static void __i915_pmu_maybe_start_timer(struct i915_pmu *pmu)
{
	if (!pmu->timer_enabled && pmu_needs_timer(pmu, true)) {
		pmu->timer_enabled = true;
		pmu->timer_last = ktime_get();
		hrtimer_start_range_ns(&pmu->timer,
				       ns_to_ktime(PERIOD), 0,
				       HRTIMER_MODE_REL_PINNED);
	}
}
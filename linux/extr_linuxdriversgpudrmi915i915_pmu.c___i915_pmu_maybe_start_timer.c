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
struct TYPE_2__ {int timer_enabled; int /*<<< orphan*/  timer; int /*<<< orphan*/  timer_last; } ;
struct drm_i915_private {TYPE_1__ pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  PERIOD ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 scalar_t__ pmu_needs_timer (struct drm_i915_private*,int) ; 

__attribute__((used)) static void __i915_pmu_maybe_start_timer(struct drm_i915_private *i915)
{
	if (!i915->pmu.timer_enabled && pmu_needs_timer(i915, true)) {
		i915->pmu.timer_enabled = true;
		i915->pmu.timer_last = ktime_get();
		hrtimer_start_range_ns(&i915->pmu.timer,
				       ns_to_ktime(PERIOD), 0,
				       HRTIMER_MODE_REL_PINNED);
	}
}
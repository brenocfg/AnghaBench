#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * event_init; int /*<<< orphan*/  event_idx; int /*<<< orphan*/  read; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  del; int /*<<< orphan*/  add; int /*<<< orphan*/  task_ctx_nr; int /*<<< orphan*/  attr_groups; } ;
struct TYPE_9__ {int /*<<< orphan*/  function; } ;
struct i915_pmu {TYPE_2__ base; TYPE_5__ timer; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; struct i915_pmu pmu; } ;
struct TYPE_8__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DRM_NOTE (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  create_event_attributes (struct i915_pmu*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_event_attributes (struct i915_pmu*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_pmu_attr_groups ; 
 int /*<<< orphan*/  i915_pmu_event_add ; 
 int /*<<< orphan*/  i915_pmu_event_del ; 
 int /*<<< orphan*/  i915_pmu_event_event_idx ; 
 int /*<<< orphan*/ * i915_pmu_event_init ; 
 int /*<<< orphan*/  i915_pmu_event_read ; 
 int /*<<< orphan*/  i915_pmu_event_start ; 
 int /*<<< orphan*/  i915_pmu_event_stop ; 
 TYPE_4__ i915_pmu_events_attr_group ; 
 int i915_pmu_register_cpuhp_state (struct i915_pmu*) ; 
 int /*<<< orphan*/  i915_sample ; 
 int /*<<< orphan*/  perf_invalid_context ; 
 int perf_pmu_register (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  perf_pmu_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void i915_pmu_register(struct drm_i915_private *i915)
{
	struct i915_pmu *pmu = &i915->pmu;
	int ret;

	if (INTEL_GEN(i915) <= 2) {
		dev_info(i915->drm.dev, "PMU not supported for this GPU.");
		return;
	}

	i915_pmu_events_attr_group.attrs = create_event_attributes(pmu);
	if (!i915_pmu_events_attr_group.attrs) {
		ret = -ENOMEM;
		goto err;
	}

	pmu->base.attr_groups	= i915_pmu_attr_groups;
	pmu->base.task_ctx_nr	= perf_invalid_context;
	pmu->base.event_init	= i915_pmu_event_init;
	pmu->base.add		= i915_pmu_event_add;
	pmu->base.del		= i915_pmu_event_del;
	pmu->base.start		= i915_pmu_event_start;
	pmu->base.stop		= i915_pmu_event_stop;
	pmu->base.read		= i915_pmu_event_read;
	pmu->base.event_idx	= i915_pmu_event_event_idx;

	spin_lock_init(&pmu->lock);
	hrtimer_init(&pmu->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	pmu->timer.function = i915_sample;

	ret = perf_pmu_register(&pmu->base, "i915", -1);
	if (ret)
		goto err;

	ret = i915_pmu_register_cpuhp_state(pmu);
	if (ret)
		goto err_unreg;

	return;

err_unreg:
	perf_pmu_unregister(&pmu->base);
err:
	pmu->base.event_init = NULL;
	free_event_attributes(pmu);
	DRM_NOTE("Failed to register PMU! (err=%d)\n", ret);
}
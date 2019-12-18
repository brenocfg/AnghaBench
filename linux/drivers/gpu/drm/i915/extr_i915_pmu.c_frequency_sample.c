#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_uncore {int dummy; } ;
struct intel_gt {struct intel_uncore* uncore; struct drm_i915_private* i915; } ;
struct i915_pmu {int enable; int /*<<< orphan*/ * sample; } ;
struct TYPE_3__ {int /*<<< orphan*/  cur_freq; } ;
struct TYPE_4__ {TYPE_1__ rps; } ;
struct drm_i915_private {TYPE_2__ gt_pm; struct i915_pmu pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_RPSTAT1 ; 
 int /*<<< orphan*/  I915_PMU_ACTUAL_FREQUENCY ; 
 int /*<<< orphan*/  I915_PMU_REQUESTED_FREQUENCY ; 
 size_t __I915_SAMPLE_FREQ_ACT ; 
 size_t __I915_SAMPLE_FREQ_REQ ; 
 int /*<<< orphan*/  add_sample_mult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int config_enabled_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_cagf (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_gt_pm_get_if_awake (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_pm_put (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_uncore_read_notrace (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
frequency_sample(struct intel_gt *gt, unsigned int period_ns)
{
	struct drm_i915_private *i915 = gt->i915;
	struct intel_uncore *uncore = gt->uncore;
	struct i915_pmu *pmu = &i915->pmu;

	if (pmu->enable & config_enabled_mask(I915_PMU_ACTUAL_FREQUENCY)) {
		u32 val;

		val = i915->gt_pm.rps.cur_freq;
		if (intel_gt_pm_get_if_awake(gt)) {
			val = intel_uncore_read_notrace(uncore, GEN6_RPSTAT1);
			val = intel_get_cagf(i915, val);
			intel_gt_pm_put(gt);
		}

		add_sample_mult(&pmu->sample[__I915_SAMPLE_FREQ_ACT],
				intel_gpu_freq(i915, val),
				period_ns / 1000);
	}

	if (pmu->enable & config_enabled_mask(I915_PMU_REQUESTED_FREQUENCY)) {
		add_sample_mult(&pmu->sample[__I915_SAMPLE_FREQ_REQ],
				intel_gpu_freq(i915, i915->gt_pm.rps.cur_freq),
				period_ns / 1000);
	}
}
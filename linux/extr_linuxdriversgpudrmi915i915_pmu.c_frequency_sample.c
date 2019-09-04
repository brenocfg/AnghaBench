#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  cur_freq; } ;
struct TYPE_7__ {TYPE_2__ rps; } ;
struct TYPE_8__ {int enable; int /*<<< orphan*/ * sample; } ;
struct TYPE_5__ {scalar_t__ awake; } ;
struct drm_i915_private {TYPE_3__ gt_pm; TYPE_4__ pmu; TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_RPSTAT1 ; 
 int /*<<< orphan*/  I915_PMU_ACTUAL_FREQUENCY ; 
 int /*<<< orphan*/  I915_PMU_REQUESTED_FREQUENCY ; 
 int /*<<< orphan*/  I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 size_t __I915_SAMPLE_FREQ_ACT ; 
 size_t __I915_SAMPLE_FREQ_REQ ; 
 int /*<<< orphan*/  add_sample_mult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int config_enabled_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_cagf (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_runtime_pm_get_if_in_use (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 

__attribute__((used)) static void
frequency_sample(struct drm_i915_private *dev_priv, unsigned int period_ns)
{
	if (dev_priv->pmu.enable &
	    config_enabled_mask(I915_PMU_ACTUAL_FREQUENCY)) {
		u32 val;

		val = dev_priv->gt_pm.rps.cur_freq;
		if (dev_priv->gt.awake &&
		    intel_runtime_pm_get_if_in_use(dev_priv)) {
			val = intel_get_cagf(dev_priv,
					     I915_READ_NOTRACE(GEN6_RPSTAT1));
			intel_runtime_pm_put(dev_priv);
		}

		add_sample_mult(&dev_priv->pmu.sample[__I915_SAMPLE_FREQ_ACT],
				intel_gpu_freq(dev_priv, val),
				period_ns / 1000);
	}

	if (dev_priv->pmu.enable &
	    config_enabled_mask(I915_PMU_REQUESTED_FREQUENCY)) {
		add_sample_mult(&dev_priv->pmu.sample[__I915_SAMPLE_FREQ_REQ],
				intel_gpu_freq(dev_priv,
					       dev_priv->gt_pm.rps.cur_freq),
				period_ns / 1000);
	}
}
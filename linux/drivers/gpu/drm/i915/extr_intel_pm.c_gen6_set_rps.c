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
typedef  scalar_t__ u8 ;
struct intel_rps {scalar_t__ cur_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int GEN6_AGGRESSIVE_TURBO ; 
 int GEN6_FREQUENCY (scalar_t__) ; 
 int GEN6_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  GEN6_RPNSWREQ ; 
 int /*<<< orphan*/  GEN6_RP_INTERRUPT_LIMITS ; 
 int GEN9_FREQUENCY (scalar_t__) ; 
 int HSW_FREQUENCY (scalar_t__) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int gen6_rps_pm_mask (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  gen6_set_rps_thresholds (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,scalar_t__) ; 
 int intel_rps_limits (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  trace_intel_gpu_freq_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen6_set_rps(struct drm_i915_private *dev_priv, u8 val)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	/* min/max delay may still have been modified so be sure to
	 * write the limits value.
	 */
	if (val != rps->cur_freq) {
		gen6_set_rps_thresholds(dev_priv, val);

		if (INTEL_GEN(dev_priv) >= 9)
			I915_WRITE(GEN6_RPNSWREQ,
				   GEN9_FREQUENCY(val));
		else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
			I915_WRITE(GEN6_RPNSWREQ,
				   HSW_FREQUENCY(val));
		else
			I915_WRITE(GEN6_RPNSWREQ,
				   GEN6_FREQUENCY(val) |
				   GEN6_OFFSET(0) |
				   GEN6_AGGRESSIVE_TURBO);
	}

	/* Make sure we continue to get interrupts
	 * until we hit the minimum or maximum frequencies.
	 */
	I915_WRITE(GEN6_RP_INTERRUPT_LIMITS, intel_rps_limits(dev_priv, val));
	I915_WRITE(GEN6_PMINTRMSK, gen6_rps_pm_mask(dev_priv, val));

	rps->cur_freq = val;
	trace_intel_gpu_freq_change(intel_gpu_freq(dev_priv, val));

	return 0;
}
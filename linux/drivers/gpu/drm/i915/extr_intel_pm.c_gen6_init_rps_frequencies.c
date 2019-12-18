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
typedef  int u32 ;
struct intel_rps {int rp0_freq; int rp1_freq; int min_freq; int max_freq; int efficient_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_RP_STATE_CAP ; 
 int /*<<< orphan*/  GEN6_RP_STATE_CAP ; 
 int GEN9_FREQ_SCALER ; 
 int /*<<< orphan*/  HSW_PCODE_DYNAMIC_DUTY_CYCLE_CONTROL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int clamp_t (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ sandybridge_pcode_read (struct drm_i915_private*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void gen6_init_rps_frequencies(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	/* All of these values are in units of 50MHz */

	/* static values from HW: RP0 > RP1 > RPn (min_freq) */
	if (IS_GEN9_LP(dev_priv)) {
		u32 rp_state_cap = I915_READ(BXT_RP_STATE_CAP);
		rps->rp0_freq = (rp_state_cap >> 16) & 0xff;
		rps->rp1_freq = (rp_state_cap >>  8) & 0xff;
		rps->min_freq = (rp_state_cap >>  0) & 0xff;
	} else {
		u32 rp_state_cap = I915_READ(GEN6_RP_STATE_CAP);
		rps->rp0_freq = (rp_state_cap >>  0) & 0xff;
		rps->rp1_freq = (rp_state_cap >>  8) & 0xff;
		rps->min_freq = (rp_state_cap >> 16) & 0xff;
	}
	/* hw_max = RP0 until we check for overclocking */
	rps->max_freq = rps->rp0_freq;

	rps->efficient_freq = rps->rp1_freq;
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv) ||
	    IS_GEN9_BC(dev_priv) || INTEL_GEN(dev_priv) >= 10) {
		u32 ddcc_status = 0;

		if (sandybridge_pcode_read(dev_priv,
					   HSW_PCODE_DYNAMIC_DUTY_CYCLE_CONTROL,
					   &ddcc_status, NULL) == 0)
			rps->efficient_freq =
				clamp_t(u8,
					((ddcc_status >> 8) & 0xff),
					rps->min_freq,
					rps->max_freq);
	}

	if (IS_GEN9_BC(dev_priv) || INTEL_GEN(dev_priv) >= 10) {
		/* Store the frequency values in 16.66 MHZ units, which is
		 * the natural hardware unit for SKL
		 */
		rps->rp0_freq *= GEN9_FREQ_SCALER;
		rps->rp1_freq *= GEN9_FREQ_SCALER;
		rps->min_freq *= GEN9_FREQ_SCALER;
		rps->max_freq *= GEN9_FREQ_SCALER;
		rps->efficient_freq *= GEN9_FREQ_SCALER;
	}
}
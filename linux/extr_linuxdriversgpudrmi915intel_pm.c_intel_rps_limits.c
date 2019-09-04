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
typedef  int u8 ;
typedef  int u32 ;
struct intel_rps {int max_freq_softlimit; int min_freq_softlimit; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static u32 intel_rps_limits(struct drm_i915_private *dev_priv, u8 val)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	u32 limits;

	/* Only set the down limit when we've reached the lowest level to avoid
	 * getting more interrupts, otherwise leave this clear. This prevents a
	 * race in the hw when coming out of rc6: There's a tiny window where
	 * the hw runs at the minimal clock before selecting the desired
	 * frequency, if the down threshold expires in that window we will not
	 * receive a down interrupt. */
	if (INTEL_GEN(dev_priv) >= 9) {
		limits = (rps->max_freq_softlimit) << 23;
		if (val <= rps->min_freq_softlimit)
			limits |= (rps->min_freq_softlimit) << 14;
	} else {
		limits = rps->max_freq_softlimit << 24;
		if (val <= rps->min_freq_softlimit)
			limits |= rps->min_freq_softlimit << 16;
	}

	return limits;
}
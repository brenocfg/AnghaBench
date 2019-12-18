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
typedef  int u32 ;
struct intel_rps {scalar_t__ min_freq_softlimit; scalar_t__ max_freq_softlimit; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int pm_rps_events; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int GEN6_PM_RP_DOWN_THRESHOLD ; 
 int GEN6_PM_RP_DOWN_TIMEOUT ; 
 int GEN6_PM_RP_UP_EI_EXPIRED ; 
 int GEN6_PM_RP_UP_THRESHOLD ; 
 int gen6_sanitize_rps_pm_mask (struct drm_i915_private*,int) ; 

__attribute__((used)) static u32 gen6_rps_pm_mask(struct drm_i915_private *dev_priv, u8 val)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	u32 mask = 0;

	/* We use UP_EI_EXPIRED interupts for both up/down in manual mode */
	if (val > rps->min_freq_softlimit)
		mask |= GEN6_PM_RP_UP_EI_EXPIRED | GEN6_PM_RP_DOWN_THRESHOLD | GEN6_PM_RP_DOWN_TIMEOUT;
	if (val < rps->max_freq_softlimit)
		mask |= GEN6_PM_RP_UP_EI_EXPIRED | GEN6_PM_RP_UP_THRESHOLD;

	mask &= dev_priv->pm_rps_events;

	return gen6_sanitize_rps_pm_mask(dev_priv, ~mask);
}
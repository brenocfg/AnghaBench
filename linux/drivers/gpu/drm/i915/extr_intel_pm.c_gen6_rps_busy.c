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
typedef  int /*<<< orphan*/  u8 ;
struct intel_rps {int /*<<< orphan*/  lock; int /*<<< orphan*/  max_freq_softlimit; int /*<<< orphan*/  min_freq_softlimit; int /*<<< orphan*/  efficient_freq; int /*<<< orphan*/  cur_freq; scalar_t__ enabled; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int pm_rps_events; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int GEN6_PM_RP_UP_EI_EXPIRED ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_enable_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_rps_pm_mask (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_rps_reset_ei (struct drm_i915_private*) ; 
 scalar_t__ intel_set_rps (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gen6_rps_busy(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	mutex_lock(&rps->lock);
	if (rps->enabled) {
		u8 freq;

		if (dev_priv->pm_rps_events & GEN6_PM_RP_UP_EI_EXPIRED)
			gen6_rps_reset_ei(dev_priv);
		I915_WRITE(GEN6_PMINTRMSK,
			   gen6_rps_pm_mask(dev_priv, rps->cur_freq));

		gen6_enable_rps_interrupts(dev_priv);

		/* Use the user's desired frequency as a guide, but for better
		 * performance, jump directly to RPe as our starting frequency.
		 */
		freq = max(rps->cur_freq,
			   rps->efficient_freq);

		if (intel_set_rps(dev_priv,
				  clamp(freq,
					rps->min_freq_softlimit,
					rps->max_freq_softlimit)))
			DRM_DEBUG_DRIVER("Failed to set idle frequency\n");
	}
	mutex_unlock(&rps->lock);
}
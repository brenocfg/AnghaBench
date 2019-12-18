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
struct intel_rps {int /*<<< orphan*/  lock; scalar_t__ last_adj; int /*<<< orphan*/  idle_freq; scalar_t__ enabled; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_disable_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_sanitize_rps_pm_mask (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_set_rps (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_set_rps_idle (struct drm_i915_private*) ; 

void gen6_rps_idle(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	/* Flush our bottom-half so that it does not race with us
	 * setting the idle frequency and so that it is bounded by
	 * our rpm wakeref. And then disable the interrupts to stop any
	 * futher RPS reclocking whilst we are asleep.
	 */
	gen6_disable_rps_interrupts(dev_priv);

	mutex_lock(&rps->lock);
	if (rps->enabled) {
		if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
			vlv_set_rps_idle(dev_priv);
		else
			gen6_set_rps(dev_priv, rps->idle_freq);
		rps->last_adj = 0;
		I915_WRITE(GEN6_PMINTRMSK,
			   gen6_sanitize_rps_pm_mask(dev_priv, ~0));
	}
	mutex_unlock(&rps->lock);
}
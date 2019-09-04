#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_dp {int /*<<< orphan*/  aux_power_domain; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pps_lock(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));

	/*
	 * See intel_power_sequencer_reset() why we need
	 * a power domain reference here.
	 */
	intel_display_power_get(dev_priv, intel_dp->aux_power_domain);

	mutex_lock(&dev_priv->pps_mutex);
}
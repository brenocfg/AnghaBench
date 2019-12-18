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
struct TYPE_2__ {scalar_t__ test_type; } ;
struct intel_dp {scalar_t__ sink_count; TYPE_1__ compliance; int /*<<< orphan*/  aux; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;

/* Variables and functions */
 scalar_t__ DP_TEST_LINK_TRAINING ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dp_cec_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_check_service_irq (struct intel_dp*) ; 
 int intel_dp_get_dpcd (struct intel_dp*) ; 
 scalar_t__ intel_dp_needs_link_retrain (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_short_pulse (struct intel_dp*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
intel_dp_short_pulse(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u8 old_sink_count = intel_dp->sink_count;
	bool ret;

	/*
	 * Clearing compliance test variables to allow capturing
	 * of values for next automated test request.
	 */
	memset(&intel_dp->compliance, 0, sizeof(intel_dp->compliance));

	/*
	 * Now read the DPCD to see if it's actually running
	 * If the current value of sink count doesn't match with
	 * the value that was stored earlier or dpcd read failed
	 * we need to do full detection
	 */
	ret = intel_dp_get_dpcd(intel_dp);

	if ((old_sink_count != intel_dp->sink_count) || !ret) {
		/* No need to proceed if we are going to do full detect */
		return false;
	}

	intel_dp_check_service_irq(intel_dp);

	/* Handle CEC interrupts, if any */
	drm_dp_cec_irq(&intel_dp->aux);

	/* defer to the hotplug work for link retraining if needed */
	if (intel_dp_needs_link_retrain(intel_dp))
		return false;

	intel_psr_short_pulse(intel_dp);

	if (intel_dp->compliance.test_type == DP_TEST_LINK_TRAINING) {
		DRM_DEBUG_KMS("Link Training Compliance Test requested\n");
		/* Send a Hotplug Uevent to userspace to start modeset */
		drm_kms_helper_hotplug_event(&dev_priv->drm);
	}

	return true;
}
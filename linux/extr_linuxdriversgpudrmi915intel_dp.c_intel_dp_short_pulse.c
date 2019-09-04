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
struct intel_dp {scalar_t__ sink_count; int* dpcd; TYPE_1__ compliance; int /*<<< orphan*/  aux; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;

/* Variables and functions */
 scalar_t__ DP_AUTOMATED_TEST_REQUEST ; 
 scalar_t__ DP_CP_IRQ ; 
 int /*<<< orphan*/  DP_DEVICE_SERVICE_IRQ_VECTOR ; 
 size_t DP_DPCD_REV ; 
 scalar_t__ DP_SINK_SPECIFIC_IRQ ; 
 scalar_t__ DP_TEST_LINK_TRAINING ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  drm_dp_cec_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (int /*<<< orphan*/ *) ; 
 int intel_dp_get_dpcd (struct intel_dp*) ; 
 scalar_t__ intel_dp_get_sink_irq (struct intel_dp*,scalar_t__*) ; 
 int /*<<< orphan*/  intel_dp_handle_test_request (struct intel_dp*) ; 
 scalar_t__ intel_dp_needs_link_retrain (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_short_pulse (struct intel_dp*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_dp_short_pulse(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));
	u8 sink_irq_vector = 0;
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

	/* Try to read the source of the interrupt */
	if (intel_dp->dpcd[DP_DPCD_REV] >= 0x11 &&
	    intel_dp_get_sink_irq(intel_dp, &sink_irq_vector) &&
	    sink_irq_vector != 0) {
		/* Clear interrupt source */
		drm_dp_dpcd_writeb(&intel_dp->aux,
				   DP_DEVICE_SERVICE_IRQ_VECTOR,
				   sink_irq_vector);

		if (sink_irq_vector & DP_AUTOMATED_TEST_REQUEST)
			intel_dp_handle_test_request(intel_dp);
		if (sink_irq_vector & (DP_CP_IRQ | DP_SINK_SPECIFIC_IRQ))
			DRM_DEBUG_DRIVER("CP or sink specific irq unhandled\n");
	}

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
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct intel_encoder {int dummy; } ;
struct TYPE_11__ {scalar_t__ i2c_defer_count; scalar_t__ i2c_nack_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  mst_state; } ;
struct intel_dp {int is_mst; int reset_link_params; int* dpcd; int detect_done; int /*<<< orphan*/  aux_power_domain; TYPE_4__ aux; int /*<<< orphan*/  desc; int /*<<< orphan*/  max_link_rate; int /*<<< orphan*/  max_link_lane_count; TYPE_5__ mst_mgr; int /*<<< orphan*/  compliance; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {scalar_t__ detect_edid; TYPE_3__ base; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  connection_mutex; } ;
struct TYPE_9__ {TYPE_1__ mode_config; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_13__ {struct intel_encoder base; } ;

/* Variables and functions */
 int DP_AUTOMATED_TEST_REQUEST ; 
 int DP_CP_IRQ ; 
 int /*<<< orphan*/  DP_DEVICE_SERVICE_IRQ_VECTOR ; 
 size_t DP_DPCD_REV ; 
 int DP_SINK_SPECIFIC_IRQ ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 TYPE_7__* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_dp_is_branch (int*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (TYPE_5__*,int) ; 
 int /*<<< orphan*/  drm_dp_read_desc (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 int edp_detect (struct intel_dp*) ; 
 struct intel_dp* intel_attached_dp (TYPE_3__*) ; 
 scalar_t__ intel_digital_port_connected (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_configure_mst (struct intel_dp*) ; 
 int intel_dp_detect_dpcd (struct intel_dp*) ; 
 scalar_t__ intel_dp_get_sink_irq (struct intel_dp*,int*) ; 
 int /*<<< orphan*/  intel_dp_handle_test_request (struct intel_dp*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_max_common_lane_count (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_max_common_rate (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_print_rates (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_retrain_link (struct intel_encoder*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  intel_dp_set_edid (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_unset_edid (struct intel_dp*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_dp_long_pulse(struct intel_connector *connector,
		    struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_dp *intel_dp = intel_attached_dp(&connector->base);
	enum drm_connector_status status;
	u8 sink_irq_vector = 0;

	WARN_ON(!drm_modeset_is_locked(&dev_priv->drm.mode_config.connection_mutex));

	intel_display_power_get(dev_priv, intel_dp->aux_power_domain);

	/* Can't disconnect eDP */
	if (intel_dp_is_edp(intel_dp))
		status = edp_detect(intel_dp);
	else if (intel_digital_port_connected(&dp_to_dig_port(intel_dp)->base))
		status = intel_dp_detect_dpcd(intel_dp);
	else
		status = connector_status_disconnected;

	if (status == connector_status_disconnected) {
		memset(&intel_dp->compliance, 0, sizeof(intel_dp->compliance));

		if (intel_dp->is_mst) {
			DRM_DEBUG_KMS("MST device may have disappeared %d vs %d\n",
				      intel_dp->is_mst,
				      intel_dp->mst_mgr.mst_state);
			intel_dp->is_mst = false;
			drm_dp_mst_topology_mgr_set_mst(&intel_dp->mst_mgr,
							intel_dp->is_mst);
		}

		goto out;
	}

	if (intel_dp->reset_link_params) {
		/* Initial max link lane count */
		intel_dp->max_link_lane_count = intel_dp_max_common_lane_count(intel_dp);

		/* Initial max link rate */
		intel_dp->max_link_rate = intel_dp_max_common_rate(intel_dp);

		intel_dp->reset_link_params = false;
	}

	intel_dp_print_rates(intel_dp);

	drm_dp_read_desc(&intel_dp->aux, &intel_dp->desc,
			 drm_dp_is_branch(intel_dp->dpcd));

	intel_dp_configure_mst(intel_dp);

	if (intel_dp->is_mst) {
		/*
		 * If we are in MST mode then this connector
		 * won't appear connected or have anything
		 * with EDID on it
		 */
		status = connector_status_disconnected;
		goto out;
	}

	/*
	 * Some external monitors do not signal loss of link synchronization
	 * with an IRQ_HPD, so force a link status check.
	 */
	if (!intel_dp_is_edp(intel_dp)) {
		struct intel_encoder *encoder = &dp_to_dig_port(intel_dp)->base;

		intel_dp_retrain_link(encoder, ctx);
	}

	/*
	 * Clearing NACK and defer counts to get their exact values
	 * while reading EDID which are required by Compliance tests
	 * 4.2.2.4 and 4.2.2.5
	 */
	intel_dp->aux.i2c_nack_count = 0;
	intel_dp->aux.i2c_defer_count = 0;

	intel_dp_set_edid(intel_dp);
	if (intel_dp_is_edp(intel_dp) || connector->detect_edid)
		status = connector_status_connected;
	intel_dp->detect_done = true;

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

out:
	if (status != connector_status_connected && !intel_dp->is_mst)
		intel_dp_unset_edid(intel_dp);

	intel_display_power_put(dev_priv, intel_dp->aux_power_domain);
	return status;
}
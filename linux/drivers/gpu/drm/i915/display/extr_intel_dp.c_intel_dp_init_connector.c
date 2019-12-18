#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_encoder {int port; int /*<<< orphan*/  hpd_pin; int /*<<< orphan*/  type; TYPE_1__ base; } ;
struct intel_dp {int reset_link_params; void* active_pipe; struct intel_connector* attached_connector; int /*<<< orphan*/  output_reg; void* DP; void* pps_pipe; } ;
struct intel_digital_port {int max_lanes; struct intel_encoder base; struct intel_dp dp; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int interlace_allowed; int ycbcr_420_allowed; TYPE_2__ base; scalar_t__ doublescan_allowed; } ;
struct intel_connector {struct drm_connector base; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  modeset_retry_work; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int DRM_MODE_CONNECTOR_DisplayPort ; 
 int DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_DP_MST (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_GMCH (struct drm_i915_private*) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 void* INVALID_PIPE ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G45 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PEG_BAND_GAP_DATA ; 
 int PORT_B ; 
 int PORT_C ; 
 int PORT_D ; 
 int PORT_F ; 
 scalar_t__ WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_connector_attach_encoder (struct intel_connector*,struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_ddi_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_dp_add_properties (struct intel_dp*,struct drm_connector*) ; 
 int /*<<< orphan*/  intel_dp_aux_fini (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_aux_init (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_connector_funcs ; 
 int /*<<< orphan*/  intel_dp_connector_helper_funcs ; 
 int /*<<< orphan*/  intel_dp_hdcp_shim ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 scalar_t__ intel_dp_is_port_edp (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_dp_modeset_retry_work_fn ; 
 int /*<<< orphan*/  intel_dp_mst_encoder_cleanup (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_dp_mst_encoder_init (struct intel_digital_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_source_rates (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_edp_init_connector (struct intel_dp*,struct intel_connector*) ; 
 int intel_hdcp_init (struct intel_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hpd_pin_default (struct drm_i915_private*,int) ; 
 int intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 
 scalar_t__ is_hdcp_supported (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  port_name (int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 void* vlv_active_pipe (struct intel_dp*) ; 

bool
intel_dp_init_connector(struct intel_digital_port *intel_dig_port,
			struct intel_connector *intel_connector)
{
	struct drm_connector *connector = &intel_connector->base;
	struct intel_dp *intel_dp = &intel_dig_port->dp;
	struct intel_encoder *intel_encoder = &intel_dig_port->base;
	struct drm_device *dev = intel_encoder->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum port port = intel_encoder->port;
	enum phy phy = intel_port_to_phy(dev_priv, port);
	int type;

	/* Initialize the work for modeset in case of link train failure */
	INIT_WORK(&intel_connector->modeset_retry_work,
		  intel_dp_modeset_retry_work_fn);

	if (WARN(intel_dig_port->max_lanes < 1,
		 "Not enough lanes (%d) for DP on port %c\n",
		 intel_dig_port->max_lanes, port_name(port)))
		return false;

	intel_dp_set_source_rates(intel_dp);

	intel_dp->reset_link_params = true;
	intel_dp->pps_pipe = INVALID_PIPE;
	intel_dp->active_pipe = INVALID_PIPE;

	/* Preserve the current hw state. */
	intel_dp->DP = I915_READ(intel_dp->output_reg);
	intel_dp->attached_connector = intel_connector;

	if (intel_dp_is_port_edp(dev_priv, port)) {
		/*
		 * Currently we don't support eDP on TypeC ports, although in
		 * theory it could work on TypeC legacy ports.
		 */
		WARN_ON(intel_phy_is_tc(dev_priv, phy));
		type = DRM_MODE_CONNECTOR_eDP;
	} else {
		type = DRM_MODE_CONNECTOR_DisplayPort;
	}

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		intel_dp->active_pipe = vlv_active_pipe(intel_dp);

	/*
	 * For eDP we always set the encoder type to INTEL_OUTPUT_EDP, but
	 * for DP the encoder type can be set by the caller to
	 * INTEL_OUTPUT_UNKNOWN for DDI, so don't rewrite it.
	 */
	if (type == DRM_MODE_CONNECTOR_eDP)
		intel_encoder->type = INTEL_OUTPUT_EDP;

	/* eDP only on port B and/or C on vlv/chv */
	if (WARN_ON((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
		    intel_dp_is_edp(intel_dp) &&
		    port != PORT_B && port != PORT_C))
		return false;

	DRM_DEBUG_KMS("Adding %s connector on port %c\n",
			type == DRM_MODE_CONNECTOR_eDP ? "eDP" : "DP",
			port_name(port));

	drm_connector_init(dev, connector, &intel_dp_connector_funcs, type);
	drm_connector_helper_add(connector, &intel_dp_connector_helper_funcs);

	if (!HAS_GMCH(dev_priv))
		connector->interlace_allowed = true;
	connector->doublescan_allowed = 0;

	if (INTEL_GEN(dev_priv) >= 11)
		connector->ycbcr_420_allowed = true;

	intel_encoder->hpd_pin = intel_hpd_pin_default(dev_priv, port);

	intel_dp_aux_init(intel_dp);

	intel_connector_attach_encoder(intel_connector, intel_encoder);

	if (HAS_DDI(dev_priv))
		intel_connector->get_hw_state = intel_ddi_connector_get_hw_state;
	else
		intel_connector->get_hw_state = intel_connector_get_hw_state;

	/* init MST on ports that can support it */
	if (HAS_DP_MST(dev_priv) && !intel_dp_is_edp(intel_dp) &&
	    (port == PORT_B || port == PORT_C ||
	     port == PORT_D || port == PORT_F))
		intel_dp_mst_encoder_init(intel_dig_port,
					  intel_connector->base.base.id);

	if (!intel_edp_init_connector(intel_dp, intel_connector)) {
		intel_dp_aux_fini(intel_dp);
		intel_dp_mst_encoder_cleanup(intel_dig_port);
		goto fail;
	}

	intel_dp_add_properties(intel_dp, connector);

	if (is_hdcp_supported(dev_priv, port) && !intel_dp_is_edp(intel_dp)) {
		int ret = intel_hdcp_init(intel_connector, &intel_dp_hdcp_shim);
		if (ret)
			DRM_DEBUG_KMS("HDCP init failed, skipping.\n");
	}

	/* For G4X desktop chip, PEG_BAND_GAP_DATA 3:0 must first be written
	 * 0xd.  Failure to do so will result in spurious interrupts being
	 * generated on the port when a cable is not attached.
	 */
	if (IS_G45(dev_priv)) {
		u32 temp = I915_READ(PEG_BAND_GAP_DATA);
		I915_WRITE(PEG_BAND_GAP_DATA, (temp & ~0xf) | 0xd);
	}

	return true;

fail:
	drm_connector_cleanup(connector);

	return false;
}
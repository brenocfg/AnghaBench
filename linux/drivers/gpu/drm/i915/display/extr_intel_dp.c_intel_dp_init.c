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
struct drm_encoder {int dummy; } ;
struct intel_encoder {int crtc_mask; int port; scalar_t__ cloneable; int /*<<< orphan*/  power_domain; int /*<<< orphan*/  type; int /*<<< orphan*/  post_disable; void* disable; void* enable; int /*<<< orphan*/  pre_enable; int /*<<< orphan*/  pre_pll_enable; int /*<<< orphan*/  post_pll_disable; int /*<<< orphan*/  suspend; int /*<<< orphan*/  update_pipe; int /*<<< orphan*/  get_config; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  compute_config; int /*<<< orphan*/  hotplug; struct drm_encoder base; } ;
struct TYPE_2__ {int /*<<< orphan*/  output_reg; } ;
struct intel_digital_port {int max_lanes; int /*<<< orphan*/  aux_ch; int /*<<< orphan*/  hpd_pulse; TYPE_1__ dp; struct intel_encoder base; } ;
struct intel_connector {int max_lanes; int /*<<< orphan*/  aux_ch; int /*<<< orphan*/  hpd_pulse; TYPE_1__ dp; struct intel_encoder base; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_D ; 
 int /*<<< orphan*/  chv_dp_post_pll_disable ; 
 int /*<<< orphan*/  chv_dp_pre_pll_enable ; 
 int /*<<< orphan*/  chv_post_disable_dp ; 
 int /*<<< orphan*/  chv_pre_enable_dp ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 scalar_t__ drm_encoder_init (int /*<<< orphan*/ *,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* g4x_disable_dp ; 
 void* g4x_enable_dp ; 
 int /*<<< orphan*/  g4x_post_disable_dp ; 
 int /*<<< orphan*/  g4x_pre_enable_dp ; 
 int /*<<< orphan*/  intel_bios_port_aux_ch (struct drm_i915_private*,int) ; 
 struct intel_digital_port* intel_connector_alloc () ; 
 int /*<<< orphan*/  intel_dp_compute_config ; 
 int /*<<< orphan*/  intel_dp_enc_funcs ; 
 int /*<<< orphan*/  intel_dp_encoder_suspend ; 
 int /*<<< orphan*/  intel_dp_get_config ; 
 int /*<<< orphan*/  intel_dp_get_hw_state ; 
 int /*<<< orphan*/  intel_dp_hotplug ; 
 int /*<<< orphan*/  intel_dp_hpd_pulse ; 
 int /*<<< orphan*/  intel_dp_init_connector (struct intel_digital_port*,struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_infoframe_init (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_panel_update_backlight ; 
 int /*<<< orphan*/  intel_port_to_power_domain (int) ; 
 int /*<<< orphan*/  kfree (struct intel_digital_port*) ; 
 struct intel_digital_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_name (int) ; 
 void* vlv_disable_dp ; 
 int /*<<< orphan*/  vlv_dp_pre_pll_enable ; 
 void* vlv_enable_dp ; 
 int /*<<< orphan*/  vlv_post_disable_dp ; 
 int /*<<< orphan*/  vlv_pre_enable_dp ; 

bool intel_dp_init(struct drm_i915_private *dev_priv,
		   i915_reg_t output_reg,
		   enum port port)
{
	struct intel_digital_port *intel_dig_port;
	struct intel_encoder *intel_encoder;
	struct drm_encoder *encoder;
	struct intel_connector *intel_connector;

	intel_dig_port = kzalloc(sizeof(*intel_dig_port), GFP_KERNEL);
	if (!intel_dig_port)
		return false;

	intel_connector = intel_connector_alloc();
	if (!intel_connector)
		goto err_connector_alloc;

	intel_encoder = &intel_dig_port->base;
	encoder = &intel_encoder->base;

	if (drm_encoder_init(&dev_priv->drm, &intel_encoder->base,
			     &intel_dp_enc_funcs, DRM_MODE_ENCODER_TMDS,
			     "DP %c", port_name(port)))
		goto err_encoder_init;

	intel_encoder->hotplug = intel_dp_hotplug;
	intel_encoder->compute_config = intel_dp_compute_config;
	intel_encoder->get_hw_state = intel_dp_get_hw_state;
	intel_encoder->get_config = intel_dp_get_config;
	intel_encoder->update_pipe = intel_panel_update_backlight;
	intel_encoder->suspend = intel_dp_encoder_suspend;
	if (IS_CHERRYVIEW(dev_priv)) {
		intel_encoder->pre_pll_enable = chv_dp_pre_pll_enable;
		intel_encoder->pre_enable = chv_pre_enable_dp;
		intel_encoder->enable = vlv_enable_dp;
		intel_encoder->disable = vlv_disable_dp;
		intel_encoder->post_disable = chv_post_disable_dp;
		intel_encoder->post_pll_disable = chv_dp_post_pll_disable;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		intel_encoder->pre_pll_enable = vlv_dp_pre_pll_enable;
		intel_encoder->pre_enable = vlv_pre_enable_dp;
		intel_encoder->enable = vlv_enable_dp;
		intel_encoder->disable = vlv_disable_dp;
		intel_encoder->post_disable = vlv_post_disable_dp;
	} else {
		intel_encoder->pre_enable = g4x_pre_enable_dp;
		intel_encoder->enable = g4x_enable_dp;
		intel_encoder->disable = g4x_disable_dp;
		intel_encoder->post_disable = g4x_post_disable_dp;
	}

	intel_dig_port->dp.output_reg = output_reg;
	intel_dig_port->max_lanes = 4;

	intel_encoder->type = INTEL_OUTPUT_DP;
	intel_encoder->power_domain = intel_port_to_power_domain(port);
	if (IS_CHERRYVIEW(dev_priv)) {
		if (port == PORT_D)
			intel_encoder->crtc_mask = 1 << 2;
		else
			intel_encoder->crtc_mask = (1 << 0) | (1 << 1);
	} else {
		intel_encoder->crtc_mask = (1 << 0) | (1 << 1) | (1 << 2);
	}
	intel_encoder->cloneable = 0;
	intel_encoder->port = port;

	intel_dig_port->hpd_pulse = intel_dp_hpd_pulse;

	if (port != PORT_A)
		intel_infoframe_init(intel_dig_port);

	intel_dig_port->aux_ch = intel_bios_port_aux_ch(dev_priv, port);
	if (!intel_dp_init_connector(intel_dig_port, intel_connector))
		goto err_init_connector;

	return true;

err_init_connector:
	drm_encoder_cleanup(encoder);
err_encoder_init:
	kfree(intel_connector);
err_connector_alloc:
	kfree(intel_dig_port);
	return false;
}
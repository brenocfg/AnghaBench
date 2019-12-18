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
struct intel_encoder {int type; int port; int crtc_mask; int cloneable; int /*<<< orphan*/  power_domain; void* enable; int /*<<< orphan*/  pre_enable; int /*<<< orphan*/  post_disable; int /*<<< orphan*/  pre_pll_enable; int /*<<< orphan*/  post_pll_disable; int /*<<< orphan*/  get_config; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  disable; int /*<<< orphan*/  compute_config; int /*<<< orphan*/  hotplug; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  hdmi_reg; } ;
struct intel_digital_port {int max_lanes; int /*<<< orphan*/  aux_ch; TYPE_2__ dp; TYPE_1__ hdmi; struct intel_encoder base; } ;
struct intel_connector {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int INTEL_OUTPUT_ANALOG ; 
 int INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INVALID_MMIO_REG ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int PORT_D ; 
 int /*<<< orphan*/  chv_hdmi_post_disable ; 
 int /*<<< orphan*/  chv_hdmi_post_pll_disable ; 
 int /*<<< orphan*/  chv_hdmi_pre_enable ; 
 int /*<<< orphan*/  chv_hdmi_pre_pll_enable ; 
 void* cpt_enable_hdmi ; 
 int /*<<< orphan*/  drm_encoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g4x_disable_hdmi ; 
 void* g4x_enable_hdmi ; 
 void* ibx_enable_hdmi ; 
 int /*<<< orphan*/  intel_bios_port_aux_ch (struct drm_i915_private*,int) ; 
 struct intel_connector* intel_connector_alloc () ; 
 int /*<<< orphan*/  intel_hdmi_compute_config ; 
 int /*<<< orphan*/  intel_hdmi_enc_funcs ; 
 int /*<<< orphan*/  intel_hdmi_get_config ; 
 int /*<<< orphan*/  intel_hdmi_get_hw_state ; 
 int /*<<< orphan*/  intel_hdmi_hotplug ; 
 int /*<<< orphan*/  intel_hdmi_init_connector (struct intel_digital_port*,struct intel_connector*) ; 
 int /*<<< orphan*/  intel_hdmi_pre_enable ; 
 int /*<<< orphan*/  intel_infoframe_init (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_port_to_power_domain (int) ; 
 int /*<<< orphan*/  kfree (struct intel_digital_port*) ; 
 struct intel_digital_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_disable_hdmi ; 
 int /*<<< orphan*/  pch_post_disable_hdmi ; 
 int /*<<< orphan*/  port_name (int) ; 
 void* vlv_enable_hdmi ; 
 int /*<<< orphan*/  vlv_hdmi_post_disable ; 
 int /*<<< orphan*/  vlv_hdmi_pre_enable ; 
 int /*<<< orphan*/  vlv_hdmi_pre_pll_enable ; 

void intel_hdmi_init(struct drm_i915_private *dev_priv,
		     i915_reg_t hdmi_reg, enum port port)
{
	struct intel_digital_port *intel_dig_port;
	struct intel_encoder *intel_encoder;
	struct intel_connector *intel_connector;

	intel_dig_port = kzalloc(sizeof(*intel_dig_port), GFP_KERNEL);
	if (!intel_dig_port)
		return;

	intel_connector = intel_connector_alloc();
	if (!intel_connector) {
		kfree(intel_dig_port);
		return;
	}

	intel_encoder = &intel_dig_port->base;

	drm_encoder_init(&dev_priv->drm, &intel_encoder->base,
			 &intel_hdmi_enc_funcs, DRM_MODE_ENCODER_TMDS,
			 "HDMI %c", port_name(port));

	intel_encoder->hotplug = intel_hdmi_hotplug;
	intel_encoder->compute_config = intel_hdmi_compute_config;
	if (HAS_PCH_SPLIT(dev_priv)) {
		intel_encoder->disable = pch_disable_hdmi;
		intel_encoder->post_disable = pch_post_disable_hdmi;
	} else {
		intel_encoder->disable = g4x_disable_hdmi;
	}
	intel_encoder->get_hw_state = intel_hdmi_get_hw_state;
	intel_encoder->get_config = intel_hdmi_get_config;
	if (IS_CHERRYVIEW(dev_priv)) {
		intel_encoder->pre_pll_enable = chv_hdmi_pre_pll_enable;
		intel_encoder->pre_enable = chv_hdmi_pre_enable;
		intel_encoder->enable = vlv_enable_hdmi;
		intel_encoder->post_disable = chv_hdmi_post_disable;
		intel_encoder->post_pll_disable = chv_hdmi_post_pll_disable;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		intel_encoder->pre_pll_enable = vlv_hdmi_pre_pll_enable;
		intel_encoder->pre_enable = vlv_hdmi_pre_enable;
		intel_encoder->enable = vlv_enable_hdmi;
		intel_encoder->post_disable = vlv_hdmi_post_disable;
	} else {
		intel_encoder->pre_enable = intel_hdmi_pre_enable;
		if (HAS_PCH_CPT(dev_priv))
			intel_encoder->enable = cpt_enable_hdmi;
		else if (HAS_PCH_IBX(dev_priv))
			intel_encoder->enable = ibx_enable_hdmi;
		else
			intel_encoder->enable = g4x_enable_hdmi;
	}

	intel_encoder->type = INTEL_OUTPUT_HDMI;
	intel_encoder->power_domain = intel_port_to_power_domain(port);
	intel_encoder->port = port;
	if (IS_CHERRYVIEW(dev_priv)) {
		if (port == PORT_D)
			intel_encoder->crtc_mask = 1 << 2;
		else
			intel_encoder->crtc_mask = (1 << 0) | (1 << 1);
	} else {
		intel_encoder->crtc_mask = (1 << 0) | (1 << 1) | (1 << 2);
	}
	intel_encoder->cloneable = 1 << INTEL_OUTPUT_ANALOG;
	/*
	 * BSpec is unclear about HDMI+HDMI cloning on g4x, but it seems
	 * to work on real hardware. And since g4x can send infoframes to
	 * only one port anyway, nothing is lost by allowing it.
	 */
	if (IS_G4X(dev_priv))
		intel_encoder->cloneable |= 1 << INTEL_OUTPUT_HDMI;

	intel_dig_port->hdmi.hdmi_reg = hdmi_reg;
	intel_dig_port->dp.output_reg = INVALID_MMIO_REG;
	intel_dig_port->max_lanes = 4;

	intel_infoframe_init(intel_dig_port);

	intel_dig_port->aux_ch = intel_bios_port_aux_ch(dev_priv, port);
	intel_hdmi_init_connector(intel_dig_port, intel_connector);
}
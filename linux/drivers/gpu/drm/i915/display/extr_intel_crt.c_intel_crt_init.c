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
typedef  int u32 ;
struct TYPE_2__ {int cloneable; int crtc_mask; int /*<<< orphan*/  base; int /*<<< orphan*/  enable; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  get_config; int /*<<< orphan*/  port; int /*<<< orphan*/  disable; int /*<<< orphan*/  compute_config; int /*<<< orphan*/  post_disable; int /*<<< orphan*/  pre_enable; int /*<<< orphan*/  pre_pll_enable; int /*<<< orphan*/  hotplug; int /*<<< orphan*/  hpd_pin; int /*<<< orphan*/  power_domain; int /*<<< orphan*/  type; } ;
struct intel_crt {TYPE_1__ base; scalar_t__ force_hotplug_required; int /*<<< orphan*/  adpa_reg; struct intel_connector* connector; } ;
struct drm_connector {int interlace_allowed; scalar_t__ doublescan_allowed; } ;
struct intel_connector {int /*<<< orphan*/  polled; int /*<<< orphan*/  get_hw_state; struct drm_connector base; } ;
struct drm_i915_private {int fdi_rx_config; int /*<<< orphan*/  drm; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADPA ; 
 int ADPA_DAC_ENABLE ; 
 int ADPA_HSYNC_CNTL_DISABLE ; 
 int ADPA_VSYNC_CNTL_DISABLE ; 
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_CONNECT ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int /*<<< orphan*/  FDI_RX_CTL (int /*<<< orphan*/ ) ; 
 int FDI_RX_LINK_REVERSAL_OVERRIDE ; 
 int FDI_RX_POLARITY_REVERSED_LPT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_LPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HPD_CRT ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int INTEL_OUTPUT_DVO ; 
 int INTEL_OUTPUT_HDMI ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCH_ADPA ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PORT_E ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  POWER_DOMAIN_PORT_CRT ; 
 int /*<<< orphan*/  VLV_ADPA ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (int /*<<< orphan*/ *,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hsw_crt_compute_config ; 
 int /*<<< orphan*/  hsw_crt_get_config ; 
 int /*<<< orphan*/  hsw_disable_crt ; 
 int /*<<< orphan*/  hsw_enable_crt ; 
 int /*<<< orphan*/  hsw_post_disable_crt ; 
 int /*<<< orphan*/  hsw_pre_enable_crt ; 
 int /*<<< orphan*/  hsw_pre_pll_enable_crt ; 
 struct intel_connector* intel_connector_alloc () ; 
 int /*<<< orphan*/  intel_connector_attach_encoder (struct intel_connector*,TYPE_1__*) ; 
 int /*<<< orphan*/  intel_connector_get_hw_state ; 
 int /*<<< orphan*/  intel_crt_compute_config ; 
 int /*<<< orphan*/  intel_crt_connector_funcs ; 
 int /*<<< orphan*/  intel_crt_connector_helper_funcs ; 
 int /*<<< orphan*/  intel_crt_enc_funcs ; 
 int /*<<< orphan*/  intel_crt_get_config ; 
 int /*<<< orphan*/  intel_crt_get_hw_state ; 
 int /*<<< orphan*/  intel_crt_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ddi_get_hw_state ; 
 int /*<<< orphan*/  intel_disable_crt ; 
 int /*<<< orphan*/  intel_enable_crt ; 
 int /*<<< orphan*/  intel_encoder_hotplug ; 
 int /*<<< orphan*/  intel_spurious_crt_detect ; 
 int /*<<< orphan*/  kfree (struct intel_crt*) ; 
 struct intel_crt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_crt_compute_config ; 
 int /*<<< orphan*/  pch_disable_crt ; 
 int /*<<< orphan*/  pch_post_disable_crt ; 

void intel_crt_init(struct drm_i915_private *dev_priv)
{
	struct drm_connector *connector;
	struct intel_crt *crt;
	struct intel_connector *intel_connector;
	i915_reg_t adpa_reg;
	u32 adpa;

	if (HAS_PCH_SPLIT(dev_priv))
		adpa_reg = PCH_ADPA;
	else if (IS_VALLEYVIEW(dev_priv))
		adpa_reg = VLV_ADPA;
	else
		adpa_reg = ADPA;

	adpa = I915_READ(adpa_reg);
	if ((adpa & ADPA_DAC_ENABLE) == 0) {
		/*
		 * On some machines (some IVB at least) CRT can be
		 * fused off, but there's no known fuse bit to
		 * indicate that. On these machine the ADPA register
		 * works normally, except the DAC enable bit won't
		 * take. So the only way to tell is attempt to enable
		 * it and see what happens.
		 */
		I915_WRITE(adpa_reg, adpa | ADPA_DAC_ENABLE |
			   ADPA_HSYNC_CNTL_DISABLE | ADPA_VSYNC_CNTL_DISABLE);
		if ((I915_READ(adpa_reg) & ADPA_DAC_ENABLE) == 0)
			return;
		I915_WRITE(adpa_reg, adpa);
	}

	crt = kzalloc(sizeof(struct intel_crt), GFP_KERNEL);
	if (!crt)
		return;

	intel_connector = intel_connector_alloc();
	if (!intel_connector) {
		kfree(crt);
		return;
	}

	connector = &intel_connector->base;
	crt->connector = intel_connector;
	drm_connector_init(&dev_priv->drm, &intel_connector->base,
			   &intel_crt_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	drm_encoder_init(&dev_priv->drm, &crt->base.base, &intel_crt_enc_funcs,
			 DRM_MODE_ENCODER_DAC, "CRT");

	intel_connector_attach_encoder(intel_connector, &crt->base);

	crt->base.type = INTEL_OUTPUT_ANALOG;
	crt->base.cloneable = (1 << INTEL_OUTPUT_DVO) | (1 << INTEL_OUTPUT_HDMI);
	if (IS_I830(dev_priv))
		crt->base.crtc_mask = (1 << 0);
	else
		crt->base.crtc_mask = (1 << 0) | (1 << 1) | (1 << 2);

	if (IS_GEN(dev_priv, 2))
		connector->interlace_allowed = 0;
	else
		connector->interlace_allowed = 1;
	connector->doublescan_allowed = 0;

	crt->adpa_reg = adpa_reg;

	crt->base.power_domain = POWER_DOMAIN_PORT_CRT;

	if (I915_HAS_HOTPLUG(dev_priv) &&
	    !dmi_check_system(intel_spurious_crt_detect)) {
		crt->base.hpd_pin = HPD_CRT;
		crt->base.hotplug = intel_encoder_hotplug;
	}

	if (HAS_DDI(dev_priv)) {
		crt->base.port = PORT_E;
		crt->base.get_config = hsw_crt_get_config;
		crt->base.get_hw_state = intel_ddi_get_hw_state;
		crt->base.compute_config = hsw_crt_compute_config;
		crt->base.pre_pll_enable = hsw_pre_pll_enable_crt;
		crt->base.pre_enable = hsw_pre_enable_crt;
		crt->base.enable = hsw_enable_crt;
		crt->base.disable = hsw_disable_crt;
		crt->base.post_disable = hsw_post_disable_crt;
	} else {
		if (HAS_PCH_SPLIT(dev_priv)) {
			crt->base.compute_config = pch_crt_compute_config;
			crt->base.disable = pch_disable_crt;
			crt->base.post_disable = pch_post_disable_crt;
		} else {
			crt->base.compute_config = intel_crt_compute_config;
			crt->base.disable = intel_disable_crt;
		}
		crt->base.port = PORT_NONE;
		crt->base.get_config = intel_crt_get_config;
		crt->base.get_hw_state = intel_crt_get_hw_state;
		crt->base.enable = intel_enable_crt;
	}
	intel_connector->get_hw_state = intel_connector_get_hw_state;

	drm_connector_helper_add(connector, &intel_crt_connector_helper_funcs);

	if (!I915_HAS_HOTPLUG(dev_priv))
		intel_connector->polled = DRM_CONNECTOR_POLL_CONNECT;

	/*
	 * Configure the automatic hotplug detection stuff
	 */
	crt->force_hotplug_required = 0;

	/*
	 * TODO: find a proper way to discover whether we need to set the the
	 * polarity and link reversal bits or not, instead of relying on the
	 * BIOS.
	 */
	if (HAS_PCH_LPT(dev_priv)) {
		u32 fdi_config = FDI_RX_POLARITY_REVERSED_LPT |
				 FDI_RX_LINK_REVERSAL_OVERRIDE;

		dev_priv->fdi_rx_config = I915_READ(FDI_RX_CTL(PIPE_A)) & fdi_config;
	}

	intel_crt_reset(&crt->base.base);
}
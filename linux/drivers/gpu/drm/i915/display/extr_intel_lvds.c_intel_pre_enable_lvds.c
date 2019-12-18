#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_lvds_encoder {int init_lvds_val; int a3_power; int /*<<< orphan*/  reg; scalar_t__ is_dual_link; int /*<<< orphan*/  init_pps; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_3__ base; } ;
struct TYPE_5__ {int lvds_border_bits; } ;
struct drm_display_mode {int flags; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int pipe_bpp; scalar_t__ dither; TYPE_2__ gmch_pfit; int /*<<< orphan*/  shared_dpll; TYPE_1__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int LVDS_A0A2_CLKA_POWER_UP ; 
 int LVDS_A3_POWER_MASK ; 
 int LVDS_B0B3_POWER_UP ; 
 int LVDS_BORDER_ENABLE ; 
 int LVDS_CLKB_POWER_UP ; 
 int LVDS_ENABLE_DITHER ; 
 int LVDS_HSYNC_POLARITY ; 
 int LVDS_PIPE_SEL (int) ; 
 int LVDS_PIPE_SEL_CPT (int) ; 
 int LVDS_PIPE_SEL_MASK ; 
 int LVDS_PIPE_SEL_MASK_CPT ; 
 int LVDS_PORT_EN ; 
 int LVDS_VSYNC_POLARITY ; 
 int /*<<< orphan*/  assert_fdi_rx_pll_disabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_pll_disabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_shared_dpll_disabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lvds_pps_init_hw (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_lvds_encoder* to_lvds_encoder (TYPE_3__*) ; 

__attribute__((used)) static void intel_pre_enable_lvds(struct intel_encoder *encoder,
				  const struct intel_crtc_state *pipe_config,
				  const struct drm_connector_state *conn_state)
{
	struct intel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc *crtc = to_intel_crtc(pipe_config->base.crtc);
	const struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	int pipe = crtc->pipe;
	u32 temp;

	if (HAS_PCH_SPLIT(dev_priv)) {
		assert_fdi_rx_pll_disabled(dev_priv, pipe);
		assert_shared_dpll_disabled(dev_priv,
					    pipe_config->shared_dpll);
	} else {
		assert_pll_disabled(dev_priv, pipe);
	}

	intel_lvds_pps_init_hw(dev_priv, &lvds_encoder->init_pps);

	temp = lvds_encoder->init_lvds_val;
	temp |= LVDS_PORT_EN | LVDS_A0A2_CLKA_POWER_UP;

	if (HAS_PCH_CPT(dev_priv)) {
		temp &= ~LVDS_PIPE_SEL_MASK_CPT;
		temp |= LVDS_PIPE_SEL_CPT(pipe);
	} else {
		temp &= ~LVDS_PIPE_SEL_MASK;
		temp |= LVDS_PIPE_SEL(pipe);
	}

	/* set the corresponsding LVDS_BORDER bit */
	temp &= ~LVDS_BORDER_ENABLE;
	temp |= pipe_config->gmch_pfit.lvds_border_bits;

	/*
	 * Set the B0-B3 data pairs corresponding to whether we're going to
	 * set the DPLLs for dual-channel mode or not.
	 */
	if (lvds_encoder->is_dual_link)
		temp |= LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP;
	else
		temp &= ~(LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP);

	/*
	 * It would be nice to set 24 vs 18-bit mode (LVDS_A3_POWER_UP)
	 * appropriately here, but we need to look more thoroughly into how
	 * panels behave in the two modes. For now, let's just maintain the
	 * value we got from the BIOS.
	 */
	temp &= ~LVDS_A3_POWER_MASK;
	temp |= lvds_encoder->a3_power;

	/*
	 * Set the dithering flag on LVDS as needed, note that there is no
	 * special lvds dither control bit on pch-split platforms, dithering is
	 * only controlled through the PIPECONF reg.
	 */
	if (IS_GEN(dev_priv, 4)) {
		/*
		 * Bspec wording suggests that LVDS port dithering only exists
		 * for 18bpp panels.
		 */
		if (pipe_config->dither && pipe_config->pipe_bpp == 18)
			temp |= LVDS_ENABLE_DITHER;
		else
			temp &= ~LVDS_ENABLE_DITHER;
	}
	temp &= ~(LVDS_HSYNC_POLARITY | LVDS_VSYNC_POLARITY);
	if (adjusted_mode->flags & DRM_MODE_FLAG_NHSYNC)
		temp |= LVDS_HSYNC_POLARITY;
	if (adjusted_mode->flags & DRM_MODE_FLAG_NVSYNC)
		temp |= LVDS_VSYNC_POLARITY;

	I915_WRITE(lvds_encoder->reg, temp);
}
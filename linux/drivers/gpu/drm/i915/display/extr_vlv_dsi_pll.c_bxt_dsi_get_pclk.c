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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_2__ base; } ;
struct intel_dsi {int lane_count; int /*<<< orphan*/  pixel_format; } ;
struct TYPE_3__ {int ctrl; } ;
struct intel_crtc_state {TYPE_1__ dsi_pll; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_DSI_PLL_CTL ; 
 int BXT_DSI_PLL_RATIO_MASK ; 
 int BXT_REF_CLOCK_KHZ ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 struct intel_dsi* enc_to_intel_dsi (TYPE_2__*) ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

u32 bxt_dsi_get_pclk(struct intel_encoder *encoder,
		     struct intel_crtc_state *config)
{
	u32 pclk;
	u32 dsi_clk;
	u32 dsi_ratio;
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	int bpp = mipi_dsi_pixel_format_to_bpp(intel_dsi->pixel_format);

	config->dsi_pll.ctrl = I915_READ(BXT_DSI_PLL_CTL);

	dsi_ratio = config->dsi_pll.ctrl & BXT_DSI_PLL_RATIO_MASK;

	dsi_clk = (dsi_ratio * BXT_REF_CLOCK_KHZ) / 2;

	pclk = DIV_ROUND_CLOSEST(dsi_clk * intel_dsi->lane_count, bpp);

	DRM_DEBUG_DRIVER("Calculated pclk=%u\n", pclk);
	return pclk;
}
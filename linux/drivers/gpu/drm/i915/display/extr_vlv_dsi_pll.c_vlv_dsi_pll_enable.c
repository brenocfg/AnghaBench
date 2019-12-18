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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct TYPE_4__ {int div; int ctrl; } ;
struct intel_crtc_state {TYPE_2__ dsi_pll; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_REG_DSI_PLL_CONTROL ; 
 int /*<<< orphan*/  CCK_REG_DSI_PLL_DIVIDER ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DSI_PLL_LOCK ; 
 int DSI_PLL_VCO_EN ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vlv_cck_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_cck_put (struct drm_i915_private*) ; 
 int vlv_cck_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_cck_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for (int,int) ; 

void vlv_dsi_pll_enable(struct intel_encoder *encoder,
			const struct intel_crtc_state *config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);

	DRM_DEBUG_KMS("\n");

	vlv_cck_get(dev_priv);

	vlv_cck_write(dev_priv, CCK_REG_DSI_PLL_CONTROL, 0);
	vlv_cck_write(dev_priv, CCK_REG_DSI_PLL_DIVIDER, config->dsi_pll.div);
	vlv_cck_write(dev_priv, CCK_REG_DSI_PLL_CONTROL,
		      config->dsi_pll.ctrl & ~DSI_PLL_VCO_EN);

	/* wait at least 0.5 us after ungating before enabling VCO,
	 * allow hrtimer subsystem optimization by relaxing timing
	 */
	usleep_range(10, 50);

	vlv_cck_write(dev_priv, CCK_REG_DSI_PLL_CONTROL, config->dsi_pll.ctrl);

	if (wait_for(vlv_cck_read(dev_priv, CCK_REG_DSI_PLL_CONTROL) &
						DSI_PLL_LOCK, 20)) {

		vlv_cck_put(dev_priv);
		DRM_ERROR("DSI PLL lock failed\n");
		return;
	}
	vlv_cck_put(dev_priv);

	DRM_DEBUG_KMS("DSI PLL locked\n");
}
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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_REG_DSI_PLL_CONTROL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DSI_PLL_LDO_GATE ; 
 int /*<<< orphan*/  DSI_PLL_VCO_EN ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_cck_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_cck_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_cck_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_cck_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vlv_dsi_pll_disable(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 tmp;

	DRM_DEBUG_KMS("\n");

	vlv_cck_get(dev_priv);

	tmp = vlv_cck_read(dev_priv, CCK_REG_DSI_PLL_CONTROL);
	tmp &= ~DSI_PLL_VCO_EN;
	tmp |= DSI_PLL_LDO_GATE;
	vlv_cck_write(dev_priv, CCK_REG_DSI_PLL_CONTROL, tmp);

	vlv_cck_put(dev_priv);
}
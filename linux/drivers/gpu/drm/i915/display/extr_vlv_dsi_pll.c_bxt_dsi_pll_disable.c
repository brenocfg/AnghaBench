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
 int /*<<< orphan*/  BXT_DSI_PLL_DO_ENABLE ; 
 int /*<<< orphan*/  BXT_DSI_PLL_ENABLE ; 
 int /*<<< orphan*/  BXT_DSI_PLL_LOCKED ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void bxt_dsi_pll_disable(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 val;

	DRM_DEBUG_KMS("\n");

	val = I915_READ(BXT_DSI_PLL_ENABLE);
	val &= ~BXT_DSI_PLL_DO_ENABLE;
	I915_WRITE(BXT_DSI_PLL_ENABLE, val);

	/*
	 * PLL lock should deassert within 200us.
	 * Wait up to 1ms before timing out.
	 */
	if (intel_de_wait_for_clear(dev_priv, BXT_DSI_PLL_ENABLE,
				    BXT_DSI_PLL_LOCKED, 1))
		DRM_ERROR("Timeout waiting for PLL lock deassertion\n");
}
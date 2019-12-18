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
struct TYPE_3__ {int dpll; } ;
struct intel_crtc_state {TYPE_1__ dpll_hw_state; } ;
struct TYPE_4__ {int lvds_ssc_freq; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEN (struct drm_i915_private*,int) ; 
 int PLLB_REF_INPUT_SPREADSPECTRUMIN ; 
 int PLL_REF_INPUT_MASK ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int i9xx_pll_refclk(struct drm_device *dev,
			   const struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 dpll = pipe_config->dpll_hw_state.dpll;

	if ((dpll & PLL_REF_INPUT_MASK) == PLLB_REF_INPUT_SPREADSPECTRUMIN)
		return dev_priv->vbt.lvds_ssc_freq;
	else if (HAS_PCH_SPLIT(dev_priv))
		return 120000;
	else if (!IS_GEN(dev_priv, 2))
		return 96000;
	else
		return 48000;
}
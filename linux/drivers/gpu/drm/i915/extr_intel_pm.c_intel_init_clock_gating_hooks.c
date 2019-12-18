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
struct TYPE_2__ {void* init_clock_gating; } ;
struct drm_i915_private {TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_DEVID (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_I85X (struct drm_i915_private*) ; 
 scalar_t__ IS_I865G (struct drm_i915_private*) ; 
 scalar_t__ IS_I965G (struct drm_i915_private*) ; 
 scalar_t__ IS_I965GM (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int /*<<< orphan*/ ) ; 
 void* bdw_init_clock_gating ; 
 void* bxt_init_clock_gating ; 
 void* cfl_init_clock_gating ; 
 void* chv_init_clock_gating ; 
 void* cnl_init_clock_gating ; 
 void* g4x_init_clock_gating ; 
 void* gen3_init_clock_gating ; 
 void* gen6_init_clock_gating ; 
 void* glk_init_clock_gating ; 
 void* hsw_init_clock_gating ; 
 void* i830_init_clock_gating ; 
 void* i85x_init_clock_gating ; 
 void* i965g_init_clock_gating ; 
 void* i965gm_init_clock_gating ; 
 void* icl_init_clock_gating ; 
 void* ilk_init_clock_gating ; 
 void* ivb_init_clock_gating ; 
 void* kbl_init_clock_gating ; 
 void* nop_init_clock_gating ; 
 void* skl_init_clock_gating ; 
 void* vlv_init_clock_gating ; 

void intel_init_clock_gating_hooks(struct drm_i915_private *dev_priv)
{
	if (IS_GEN(dev_priv, 12))
		dev_priv->display.init_clock_gating = nop_init_clock_gating;
	else if (IS_GEN(dev_priv, 11))
		dev_priv->display.init_clock_gating = icl_init_clock_gating;
	else if (IS_CANNONLAKE(dev_priv))
		dev_priv->display.init_clock_gating = cnl_init_clock_gating;
	else if (IS_COFFEELAKE(dev_priv))
		dev_priv->display.init_clock_gating = cfl_init_clock_gating;
	else if (IS_SKYLAKE(dev_priv))
		dev_priv->display.init_clock_gating = skl_init_clock_gating;
	else if (IS_KABYLAKE(dev_priv))
		dev_priv->display.init_clock_gating = kbl_init_clock_gating;
	else if (IS_BROXTON(dev_priv))
		dev_priv->display.init_clock_gating = bxt_init_clock_gating;
	else if (IS_GEMINILAKE(dev_priv))
		dev_priv->display.init_clock_gating = glk_init_clock_gating;
	else if (IS_BROADWELL(dev_priv))
		dev_priv->display.init_clock_gating = bdw_init_clock_gating;
	else if (IS_CHERRYVIEW(dev_priv))
		dev_priv->display.init_clock_gating = chv_init_clock_gating;
	else if (IS_HASWELL(dev_priv))
		dev_priv->display.init_clock_gating = hsw_init_clock_gating;
	else if (IS_IVYBRIDGE(dev_priv))
		dev_priv->display.init_clock_gating = ivb_init_clock_gating;
	else if (IS_VALLEYVIEW(dev_priv))
		dev_priv->display.init_clock_gating = vlv_init_clock_gating;
	else if (IS_GEN(dev_priv, 6))
		dev_priv->display.init_clock_gating = gen6_init_clock_gating;
	else if (IS_GEN(dev_priv, 5))
		dev_priv->display.init_clock_gating = ilk_init_clock_gating;
	else if (IS_G4X(dev_priv))
		dev_priv->display.init_clock_gating = g4x_init_clock_gating;
	else if (IS_I965GM(dev_priv))
		dev_priv->display.init_clock_gating = i965gm_init_clock_gating;
	else if (IS_I965G(dev_priv))
		dev_priv->display.init_clock_gating = i965g_init_clock_gating;
	else if (IS_GEN(dev_priv, 3))
		dev_priv->display.init_clock_gating = gen3_init_clock_gating;
	else if (IS_I85X(dev_priv) || IS_I865G(dev_priv))
		dev_priv->display.init_clock_gating = i85x_init_clock_gating;
	else if (IS_GEN(dev_priv, 2))
		dev_priv->display.init_clock_gating = i830_init_clock_gating;
	else {
		MISSING_CASE(INTEL_DEVID(dev_priv));
		dev_priv->display.init_clock_gating = nop_init_clock_gating;
	}
}
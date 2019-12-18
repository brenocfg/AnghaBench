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
struct TYPE_2__ {void* get_cdclk; void* modeset_calc_cdclk; int /*<<< orphan*/  set_cdclk; } ;
struct drm_i915_private {TYPE_1__ display; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G33 (struct drm_i915_private*) ; 
 scalar_t__ IS_G45 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_GM45 (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_I845G (struct drm_i915_private*) ; 
 scalar_t__ IS_I85X (struct drm_i915_private*) ; 
 scalar_t__ IS_I865G (struct drm_i915_private*) ; 
 scalar_t__ IS_I915G (struct drm_i915_private*) ; 
 scalar_t__ IS_I915GM (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_I965G (struct drm_i915_private*) ; 
 scalar_t__ IS_I965GM (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 void* bdw_get_cdclk ; 
 void* bdw_modeset_calc_cdclk ; 
 int /*<<< orphan*/  bdw_set_cdclk ; 
 void* bxt_get_cdclk ; 
 void* bxt_modeset_calc_cdclk ; 
 int /*<<< orphan*/  bxt_set_cdclk ; 
 int /*<<< orphan*/  chv_set_cdclk ; 
 void* cnl_get_cdclk ; 
 void* cnl_modeset_calc_cdclk ; 
 int /*<<< orphan*/  cnl_set_cdclk ; 
 void* fixed_133mhz_get_cdclk ; 
 void* fixed_200mhz_get_cdclk ; 
 void* fixed_266mhz_get_cdclk ; 
 void* fixed_333mhz_get_cdclk ; 
 void* fixed_400mhz_get_cdclk ; 
 void* fixed_450mhz_get_cdclk ; 
 void* g33_get_cdclk ; 
 void* gm45_get_cdclk ; 
 void* hsw_get_cdclk ; 
 void* i85x_get_cdclk ; 
 void* i915gm_get_cdclk ; 
 void* i945gm_get_cdclk ; 
 void* i965gm_get_cdclk ; 
 void* icl_get_cdclk ; 
 void* icl_modeset_calc_cdclk ; 
 int /*<<< orphan*/  icl_set_cdclk ; 
 void* pnv_get_cdclk ; 
 void* skl_get_cdclk ; 
 void* skl_modeset_calc_cdclk ; 
 int /*<<< orphan*/  skl_set_cdclk ; 
 void* vlv_get_cdclk ; 
 void* vlv_modeset_calc_cdclk ; 
 int /*<<< orphan*/  vlv_set_cdclk ; 

void intel_init_cdclk_hooks(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 11) {
		dev_priv->display.set_cdclk = icl_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = icl_modeset_calc_cdclk;
	} else if (IS_CANNONLAKE(dev_priv)) {
		dev_priv->display.set_cdclk = cnl_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = cnl_modeset_calc_cdclk;
	} else if (IS_GEN9_LP(dev_priv)) {
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
	} else if (IS_GEN9_BC(dev_priv)) {
		dev_priv->display.set_cdclk = skl_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = skl_modeset_calc_cdclk;
	} else if (IS_BROADWELL(dev_priv)) {
		dev_priv->display.set_cdclk = bdw_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = bdw_modeset_calc_cdclk;
	} else if (IS_CHERRYVIEW(dev_priv)) {
		dev_priv->display.set_cdclk = chv_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = vlv_modeset_calc_cdclk;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		dev_priv->display.set_cdclk = vlv_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = vlv_modeset_calc_cdclk;
	}

	if (INTEL_GEN(dev_priv) >= 11)
		dev_priv->display.get_cdclk = icl_get_cdclk;
	else if (IS_CANNONLAKE(dev_priv))
		dev_priv->display.get_cdclk = cnl_get_cdclk;
	else if (IS_GEN9_LP(dev_priv))
		dev_priv->display.get_cdclk = bxt_get_cdclk;
	else if (IS_GEN9_BC(dev_priv))
		dev_priv->display.get_cdclk = skl_get_cdclk;
	else if (IS_BROADWELL(dev_priv))
		dev_priv->display.get_cdclk = bdw_get_cdclk;
	else if (IS_HASWELL(dev_priv))
		dev_priv->display.get_cdclk = hsw_get_cdclk;
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->display.get_cdclk = vlv_get_cdclk;
	else if (IS_GEN(dev_priv, 6) || IS_IVYBRIDGE(dev_priv))
		dev_priv->display.get_cdclk = fixed_400mhz_get_cdclk;
	else if (IS_GEN(dev_priv, 5))
		dev_priv->display.get_cdclk = fixed_450mhz_get_cdclk;
	else if (IS_GM45(dev_priv))
		dev_priv->display.get_cdclk = gm45_get_cdclk;
	else if (IS_G45(dev_priv))
		dev_priv->display.get_cdclk = g33_get_cdclk;
	else if (IS_I965GM(dev_priv))
		dev_priv->display.get_cdclk = i965gm_get_cdclk;
	else if (IS_I965G(dev_priv))
		dev_priv->display.get_cdclk = fixed_400mhz_get_cdclk;
	else if (IS_PINEVIEW(dev_priv))
		dev_priv->display.get_cdclk = pnv_get_cdclk;
	else if (IS_G33(dev_priv))
		dev_priv->display.get_cdclk = g33_get_cdclk;
	else if (IS_I945GM(dev_priv))
		dev_priv->display.get_cdclk = i945gm_get_cdclk;
	else if (IS_I945G(dev_priv))
		dev_priv->display.get_cdclk = fixed_400mhz_get_cdclk;
	else if (IS_I915GM(dev_priv))
		dev_priv->display.get_cdclk = i915gm_get_cdclk;
	else if (IS_I915G(dev_priv))
		dev_priv->display.get_cdclk = fixed_333mhz_get_cdclk;
	else if (IS_I865G(dev_priv))
		dev_priv->display.get_cdclk = fixed_266mhz_get_cdclk;
	else if (IS_I85X(dev_priv))
		dev_priv->display.get_cdclk = i85x_get_cdclk;
	else if (IS_I845G(dev_priv))
		dev_priv->display.get_cdclk = fixed_200mhz_get_cdclk;
	else { /* 830 */
		WARN(!IS_I830(dev_priv),
		     "Unknown platform. Assuming 133 MHz CDCLK\n");
		dev_priv->display.get_cdclk = fixed_133mhz_get_cdclk;
	}
}
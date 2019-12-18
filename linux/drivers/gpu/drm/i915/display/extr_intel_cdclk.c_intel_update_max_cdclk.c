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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int ref; int cdclk; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {int max_cdclk_freq; int skl_preferred_vco_freq; int max_dotclk_freq; TYPE_2__ cdclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  FUSE_STRAP ; 
 int HSW_CDCLK_LIMIT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BDW_ULT (struct drm_i915_private*) ; 
 scalar_t__ IS_BDW_ULX (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SKL_DFSM ; 
 scalar_t__ SKL_DFSM_CDCLK_LIMIT_450 ; 
 scalar_t__ SKL_DFSM_CDCLK_LIMIT_540 ; 
 scalar_t__ SKL_DFSM_CDCLK_LIMIT_675 ; 
 int SKL_DFSM_CDCLK_LIMIT_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int intel_compute_max_dotclk (struct drm_i915_private*) ; 
 int skl_calc_cdclk (int,int) ; 

void intel_update_max_cdclk(struct drm_i915_private *dev_priv)
{
	if (IS_ELKHARTLAKE(dev_priv)) {
		if (dev_priv->cdclk.hw.ref == 24000)
			dev_priv->max_cdclk_freq = 552000;
		else
			dev_priv->max_cdclk_freq = 556800;
	} else if (INTEL_GEN(dev_priv) >= 11) {
		if (dev_priv->cdclk.hw.ref == 24000)
			dev_priv->max_cdclk_freq = 648000;
		else
			dev_priv->max_cdclk_freq = 652800;
	} else if (IS_CANNONLAKE(dev_priv)) {
		dev_priv->max_cdclk_freq = 528000;
	} else if (IS_GEN9_BC(dev_priv)) {
		u32 limit = I915_READ(SKL_DFSM) & SKL_DFSM_CDCLK_LIMIT_MASK;
		int max_cdclk, vco;

		vco = dev_priv->skl_preferred_vco_freq;
		WARN_ON(vco != 8100000 && vco != 8640000);

		/*
		 * Use the lower (vco 8640) cdclk values as a
		 * first guess. skl_calc_cdclk() will correct it
		 * if the preferred vco is 8100 instead.
		 */
		if (limit == SKL_DFSM_CDCLK_LIMIT_675)
			max_cdclk = 617143;
		else if (limit == SKL_DFSM_CDCLK_LIMIT_540)
			max_cdclk = 540000;
		else if (limit == SKL_DFSM_CDCLK_LIMIT_450)
			max_cdclk = 432000;
		else
			max_cdclk = 308571;

		dev_priv->max_cdclk_freq = skl_calc_cdclk(max_cdclk, vco);
	} else if (IS_GEMINILAKE(dev_priv)) {
		dev_priv->max_cdclk_freq = 316800;
	} else if (IS_BROXTON(dev_priv)) {
		dev_priv->max_cdclk_freq = 624000;
	} else if (IS_BROADWELL(dev_priv))  {
		/*
		 * FIXME with extra cooling we can allow
		 * 540 MHz for ULX and 675 Mhz for ULT.
		 * How can we know if extra cooling is
		 * available? PCI ID, VTB, something else?
		 */
		if (I915_READ(FUSE_STRAP) & HSW_CDCLK_LIMIT)
			dev_priv->max_cdclk_freq = 450000;
		else if (IS_BDW_ULX(dev_priv))
			dev_priv->max_cdclk_freq = 450000;
		else if (IS_BDW_ULT(dev_priv))
			dev_priv->max_cdclk_freq = 540000;
		else
			dev_priv->max_cdclk_freq = 675000;
	} else if (IS_CHERRYVIEW(dev_priv)) {
		dev_priv->max_cdclk_freq = 320000;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		dev_priv->max_cdclk_freq = 400000;
	} else {
		/* otherwise assume cdclk is fixed */
		dev_priv->max_cdclk_freq = dev_priv->cdclk.hw.cdclk;
	}

	dev_priv->max_dotclk_freq = intel_compute_max_dotclk(dev_priv);

	DRM_DEBUG_DRIVER("Max CD clock rate: %d kHz\n",
			 dev_priv->max_cdclk_freq);

	DRM_DEBUG_DRIVER("Max dotclock rate: %d kHz\n",
			 dev_priv->max_dotclk_freq);
}
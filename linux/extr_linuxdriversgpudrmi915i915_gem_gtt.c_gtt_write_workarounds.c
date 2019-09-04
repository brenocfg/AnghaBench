#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int GAMW_ECO_ENABLE_64K_IPS_FIELD ; 
 int /*<<< orphan*/  GEN8_GAMW_ECO_DEV_RW_IA ; 
 int /*<<< orphan*/  GEN8_L3_LRA_1_GPGPU ; 
 int GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_BDW ; 
 int GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_CHV ; 
 int GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_BXT ; 
 int GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_SKL ; 
 scalar_t__ HAS_PAGE_SIZES (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_64K ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 

__attribute__((used)) static void gtt_write_workarounds(struct drm_i915_private *dev_priv)
{
	/* This function is for gtt related workarounds. This function is
	 * called on driver load and after a GPU reset, so you can place
	 * workarounds here even if they get overwritten by GPU reset.
	 */
	/* WaIncreaseDefaultTLBEntries:chv,bdw,skl,bxt,kbl,glk,cfl,cnl,icl */
	if (IS_BROADWELL(dev_priv))
		I915_WRITE(GEN8_L3_LRA_1_GPGPU, GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_BDW);
	else if (IS_CHERRYVIEW(dev_priv))
		I915_WRITE(GEN8_L3_LRA_1_GPGPU, GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_CHV);
	else if (IS_GEN9_LP(dev_priv))
		I915_WRITE(GEN8_L3_LRA_1_GPGPU, GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_BXT);
	else if (INTEL_GEN(dev_priv) >= 9)
		I915_WRITE(GEN8_L3_LRA_1_GPGPU, GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_SKL);

	/*
	 * To support 64K PTEs we need to first enable the use of the
	 * Intermediate-Page-Size(IPS) bit of the PDE field via some magical
	 * mmio, otherwise the page-walker will simply ignore the IPS bit. This
	 * shouldn't be needed after GEN10.
	 *
	 * 64K pages were first introduced from BDW+, although technically they
	 * only *work* from gen9+. For pre-BDW we instead have the option for
	 * 32K pages, but we don't currently have any support for it in our
	 * driver.
	 */
	if (HAS_PAGE_SIZES(dev_priv, I915_GTT_PAGE_SIZE_64K) &&
	    INTEL_GEN(dev_priv) <= 10)
		I915_WRITE(GEN8_GAMW_ECO_DEV_RW_IA,
			   I915_READ(GEN8_GAMW_ECO_DEV_RW_IA) |
			   GAMW_ECO_ENABLE_64K_IPS_FIELD);
}
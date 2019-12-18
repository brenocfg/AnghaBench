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
struct intel_uncore {int dummy; } ;
struct intel_gt {struct intel_uncore* uncore; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMW_ECO_ENABLE_64K_IPS_FIELD ; 
 int /*<<< orphan*/  GEN8_GAMW_ECO_DEV_RW_IA ; 
 int /*<<< orphan*/  GEN8_L3_LRA_1_GPGPU ; 
 int /*<<< orphan*/  GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_BDW ; 
 int /*<<< orphan*/  GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_CHV ; 
 int /*<<< orphan*/  GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_BXT ; 
 int /*<<< orphan*/  GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_SKL ; 
 int /*<<< orphan*/  GTT_CACHE_EN_ALL ; 
 scalar_t__ HAS_PAGE_SIZES (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_GTT_CACHE_EN ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_2M ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_64K ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_rmw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gtt_write_workarounds(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;
	struct intel_uncore *uncore = gt->uncore;

	/* This function is for gtt related workarounds. This function is
	 * called on driver load and after a GPU reset, so you can place
	 * workarounds here even if they get overwritten by GPU reset.
	 */
	/* WaIncreaseDefaultTLBEntries:chv,bdw,skl,bxt,kbl,glk,cfl,cnl,icl */
	if (IS_BROADWELL(i915))
		intel_uncore_write(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_BDW);
	else if (IS_CHERRYVIEW(i915))
		intel_uncore_write(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_CHV);
	else if (IS_GEN9_LP(i915))
		intel_uncore_write(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_BXT);
	else if (INTEL_GEN(i915) >= 9)
		intel_uncore_write(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_SKL);

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
	if (HAS_PAGE_SIZES(i915, I915_GTT_PAGE_SIZE_64K) &&
	    INTEL_GEN(i915) <= 10)
		intel_uncore_rmw(uncore,
				 GEN8_GAMW_ECO_DEV_RW_IA,
				 0,
				 GAMW_ECO_ENABLE_64K_IPS_FIELD);

	if (IS_GEN_RANGE(i915, 8, 11)) {
		bool can_use_gtt_cache = true;

		/*
		 * According to the BSpec if we use 2M/1G pages then we also
		 * need to disable the GTT cache. At least on BDW we can see
		 * visual corruption when using 2M pages, and not disabling the
		 * GTT cache.
		 */
		if (HAS_PAGE_SIZES(i915, I915_GTT_PAGE_SIZE_2M))
			can_use_gtt_cache = false;

		/* WaGttCachingOffByDefault */
		intel_uncore_write(uncore,
				   HSW_GTT_CACHE_EN,
				   can_use_gtt_cache ? GTT_CACHE_EN_ALL : 0);
		WARN_ON_ONCE(can_use_gtt_cache &&
			     intel_uncore_read(uncore,
					       HSW_GTT_CACHE_EN) == 0);
	}
}
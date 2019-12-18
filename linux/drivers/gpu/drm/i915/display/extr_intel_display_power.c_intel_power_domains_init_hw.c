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
struct i915_power_domains {int initializing; int /*<<< orphan*/  wakeref; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable_power_well; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_PCH_NOP (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  assert_isp_power_gated (struct drm_i915_private*) ; 
 int /*<<< orphan*/  assert_ved_power_gated (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  chv_phy_control_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  hsw_assert_cdclk (struct drm_i915_private*) ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  icl_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pch_reset_handshake (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_power_domains_sync_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_cmnlane_wa (struct drm_i915_private*) ; 

void intel_power_domains_init_hw(struct drm_i915_private *i915, bool resume)
{
	struct i915_power_domains *power_domains = &i915->power_domains;

	power_domains->initializing = true;

	if (INTEL_GEN(i915) >= 11) {
		icl_display_core_init(i915, resume);
	} else if (IS_CANNONLAKE(i915)) {
		cnl_display_core_init(i915, resume);
	} else if (IS_GEN9_BC(i915)) {
		skl_display_core_init(i915, resume);
	} else if (IS_GEN9_LP(i915)) {
		bxt_display_core_init(i915, resume);
	} else if (IS_CHERRYVIEW(i915)) {
		mutex_lock(&power_domains->lock);
		chv_phy_control_init(i915);
		mutex_unlock(&power_domains->lock);
		assert_isp_power_gated(i915);
	} else if (IS_VALLEYVIEW(i915)) {
		mutex_lock(&power_domains->lock);
		vlv_cmnlane_wa(i915);
		mutex_unlock(&power_domains->lock);
		assert_ved_power_gated(i915);
		assert_isp_power_gated(i915);
	} else if (IS_BROADWELL(i915) || IS_HASWELL(i915)) {
		hsw_assert_cdclk(i915);
		intel_pch_reset_handshake(i915, !HAS_PCH_NOP(i915));
	} else if (IS_IVYBRIDGE(i915)) {
		intel_pch_reset_handshake(i915, !HAS_PCH_NOP(i915));
	}

	/*
	 * Keep all power wells enabled for any dependent HW access during
	 * initialization and to make sure we keep BIOS enabled display HW
	 * resources powered until display HW readout is complete. We drop
	 * this reference in intel_power_domains_enable().
	 */
	power_domains->wakeref =
		intel_display_power_get(i915, POWER_DOMAIN_INIT);

	/* Disable power support if the user asked so. */
	if (!i915_modparams.disable_power_well)
		intel_display_power_get(i915, POWER_DOMAIN_INIT);
	intel_power_domains_sync_hw(i915);

	power_domains->initializing = false;
}
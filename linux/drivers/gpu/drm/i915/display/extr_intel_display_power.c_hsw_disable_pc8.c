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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ HAS_PCH_LPT_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_LP_PARTITION_LEVEL_DISABLE ; 
 int /*<<< orphan*/  SOUTH_DSPCLK_GATE_D ; 
 int /*<<< orphan*/  hsw_restore_lcpll (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_pch_refclk (struct drm_i915_private*) ; 

__attribute__((used)) static void hsw_disable_pc8(struct drm_i915_private *dev_priv)
{
	u32 val;

	DRM_DEBUG_KMS("Disabling package C8+\n");

	hsw_restore_lcpll(dev_priv);
	intel_init_pch_refclk(dev_priv);

	if (HAS_PCH_LPT_LP(dev_priv)) {
		val = I915_READ(SOUTH_DSPCLK_GATE_D);
		val |= PCH_LP_PARTITION_LEVEL_DISABLE;
		I915_WRITE(SOUTH_DSPCLK_GATE_D, val);
	}
}
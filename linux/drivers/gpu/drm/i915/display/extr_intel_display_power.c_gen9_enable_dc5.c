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
 int /*<<< orphan*/  DC_STATE_EN_UPTO_DC5 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  GEN8_CHICKEN_DCPR_1 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 int SKL_SELECT_ALTERNATE_DC_EXIT ; 
 int /*<<< orphan*/  assert_can_enable_dc5 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen9_enable_dc5(struct drm_i915_private *dev_priv)
{
	assert_can_enable_dc5(dev_priv);

	DRM_DEBUG_KMS("Enabling DC5\n");

	/* Wa Display #1183: skl,kbl,cfl */
	if (IS_GEN9_BC(dev_priv))
		I915_WRITE(GEN8_CHICKEN_DCPR_1, I915_READ(GEN8_CHICKEN_DCPR_1) |
			   SKL_SELECT_ALTERNATE_DC_EXIT);

	gen9_set_dc_state(dev_priv, DC_STATE_EN_UPTO_DC5);
}
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
 int /*<<< orphan*/  CHICKEN_MISC_2 ; 
 int /*<<< orphan*/  CNL_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_combo_phy_verify_state (struct drm_i915_private*) ; 

__attribute__((used)) static void cnl_combo_phys_uninit(struct drm_i915_private *dev_priv)
{
	u32 val;

	if (!cnl_combo_phy_verify_state(dev_priv))
		DRM_WARN("Combo PHY HW state changed unexpectedly.\n");

	val = I915_READ(CHICKEN_MISC_2);
	val |= CNL_COMP_PWR_DOWN;
	I915_WRITE(CHICKEN_MISC_2, val);
}
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
 int /*<<< orphan*/  CHICKEN_MISC_2 ; 
 int CNL_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  CNL_PORT_COMP_DW0 ; 
 int COMP_INIT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cnl_combo_phy_enabled(struct drm_i915_private *dev_priv)
{
	return !(I915_READ(CHICKEN_MISC_2) & CNL_COMP_PWR_DOWN) &&
		(I915_READ(CNL_PORT_COMP_DW0) & COMP_INIT);
}
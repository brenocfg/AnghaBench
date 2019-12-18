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
 int /*<<< orphan*/  CL_POWER_DOWN_ENABLE ; 
 int /*<<< orphan*/  CNL_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  CNL_PORT_CL1CM_DW5 ; 
 int /*<<< orphan*/  CNL_PORT_COMP_DW0 ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_A ; 
 int /*<<< orphan*/  cnl_set_procmon_ref_values (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_combo_phys_init(struct drm_i915_private *dev_priv)
{
	u32 val;

	val = I915_READ(CHICKEN_MISC_2);
	val &= ~CNL_COMP_PWR_DOWN;
	I915_WRITE(CHICKEN_MISC_2, val);

	/* Dummy PORT_A to get the correct CNL register from the ICL macro */
	cnl_set_procmon_ref_values(dev_priv, PHY_A);

	val = I915_READ(CNL_PORT_COMP_DW0);
	val |= COMP_INIT;
	I915_WRITE(CNL_PORT_COMP_DW0, val);

	val = I915_READ(CNL_PORT_CL1CM_DW5);
	val |= CL_POWER_DOWN_ENABLE;
	I915_WRITE(CNL_PORT_CL1CM_DW5, val);
}
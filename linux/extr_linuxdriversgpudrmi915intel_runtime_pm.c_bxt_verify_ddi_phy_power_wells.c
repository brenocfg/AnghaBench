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
struct TYPE_2__ {int /*<<< orphan*/  phy; } ;
struct i915_power_well {scalar_t__ count; TYPE_1__ bxt; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_DPIO_CMN_A ; 
 int /*<<< orphan*/  BXT_DPIO_CMN_BC ; 
 int /*<<< orphan*/  GLK_DPIO_CMN_C ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_ddi_phy_verify_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_verify_ddi_phy_power_wells(struct drm_i915_private *dev_priv)
{
	struct i915_power_well *power_well;

	power_well = lookup_power_well(dev_priv, BXT_DPIO_CMN_A);
	if (power_well->count > 0)
		bxt_ddi_phy_verify_state(dev_priv, power_well->bxt.phy);

	power_well = lookup_power_well(dev_priv, BXT_DPIO_CMN_BC);
	if (power_well->count > 0)
		bxt_ddi_phy_verify_state(dev_priv, power_well->bxt.phy);

	if (IS_GEMINILAKE(dev_priv)) {
		power_well = lookup_power_well(dev_priv, GLK_DPIO_CMN_C);
		if (power_well->count > 0)
			bxt_ddi_phy_verify_state(dev_priv, power_well->bxt.phy);
	}
}
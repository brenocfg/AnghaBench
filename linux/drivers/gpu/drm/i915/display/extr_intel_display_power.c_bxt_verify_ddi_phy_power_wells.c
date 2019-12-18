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
struct i915_power_well {scalar_t__ count; TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy; } ;
struct TYPE_4__ {TYPE_1__ bxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_DISP_PW_DPIO_CMN_A ; 
 int /*<<< orphan*/  GLK_DISP_PW_DPIO_CMN_C ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  VLV_DISP_PW_DPIO_CMN_BC ; 
 int /*<<< orphan*/  bxt_ddi_phy_verify_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_verify_ddi_phy_power_wells(struct drm_i915_private *dev_priv)
{
	struct i915_power_well *power_well;

	power_well = lookup_power_well(dev_priv, BXT_DISP_PW_DPIO_CMN_A);
	if (power_well->count > 0)
		bxt_ddi_phy_verify_state(dev_priv, power_well->desc->bxt.phy);

	power_well = lookup_power_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	if (power_well->count > 0)
		bxt_ddi_phy_verify_state(dev_priv, power_well->desc->bxt.phy);

	if (IS_GEMINILAKE(dev_priv)) {
		power_well = lookup_power_well(dev_priv,
					       GLK_DISP_PW_DPIO_CMN_C);
		if (power_well->count > 0)
			bxt_ddi_phy_verify_state(dev_priv,
						 power_well->desc->bxt.phy);
	}
}
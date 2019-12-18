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
struct i915_power_well {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsw_power_well_disable (struct drm_i915_private*,struct i915_power_well*) ; 
 int /*<<< orphan*/  icl_tc_port_assert_ref_held (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void
icl_tc_phy_aux_power_well_disable(struct drm_i915_private *dev_priv,
				  struct i915_power_well *power_well)
{
	icl_tc_port_assert_ref_held(dev_priv, power_well);

	hsw_power_well_disable(dev_priv, power_well);
}
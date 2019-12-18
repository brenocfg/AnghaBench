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
struct i915_power_well {scalar_t__ count; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i830_pipes_power_well_disable (struct drm_i915_private*,struct i915_power_well*) ; 
 int /*<<< orphan*/  i830_pipes_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void i830_pipes_power_well_sync_hw(struct drm_i915_private *dev_priv,
					  struct i915_power_well *power_well)
{
	if (power_well->count > 0)
		i830_pipes_power_well_enable(dev_priv, power_well);
	else
		i830_pipes_power_well_disable(dev_priv, power_well);
}
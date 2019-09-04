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
struct i915_power_well {int id; } ;
struct i915_power_domains {int power_well_count; struct i915_power_well* power_wells; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;

/* Variables and functions */

__attribute__((used)) static struct i915_power_well *
lookup_power_well(struct drm_i915_private *dev_priv,
		  enum i915_power_well_id power_well_id)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	int i;

	for (i = 0; i < power_domains->power_well_count; i++) {
		struct i915_power_well *power_well;

		power_well = &power_domains->power_wells[i];
		if (power_well->id == power_well_id)
			return power_well;
	}

	return NULL;
}
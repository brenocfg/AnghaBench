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
typedef  int u64 ;
struct i915_power_domains {int power_well_count; TYPE_1__* power_wells; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;
typedef  int /*<<< orphan*/  power_well_ids ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void assert_power_well_ids_unique(struct drm_i915_private *dev_priv)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	u64 power_well_ids;
	int i;

	power_well_ids = 0;
	for (i = 0; i < power_domains->power_well_count; i++) {
		enum i915_power_well_id id = power_domains->power_wells[i].id;

		WARN_ON(id >= sizeof(power_well_ids) * 8);
		WARN_ON(power_well_ids & BIT_ULL(id));
		power_well_ids |= BIT_ULL(id);
	}
}
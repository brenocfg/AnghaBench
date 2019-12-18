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
struct i915_power_well_desc {int id; } ;
struct i915_power_domains {int power_well_count; TYPE_1__* power_wells; } ;
typedef  int /*<<< orphan*/  power_well_ids ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;
struct TYPE_2__ {struct i915_power_well_desc const* desc; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int DISP_PW_ID_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__set_power_wells(struct i915_power_domains *power_domains,
		  const struct i915_power_well_desc *power_well_descs,
		  int power_well_count)
{
	u64 power_well_ids = 0;
	int i;

	power_domains->power_well_count = power_well_count;
	power_domains->power_wells =
				kcalloc(power_well_count,
					sizeof(*power_domains->power_wells),
					GFP_KERNEL);
	if (!power_domains->power_wells)
		return -ENOMEM;

	for (i = 0; i < power_well_count; i++) {
		enum i915_power_well_id id = power_well_descs[i].id;

		power_domains->power_wells[i].desc = &power_well_descs[i];

		if (id == DISP_PW_ID_NONE)
			continue;

		WARN_ON(id >= sizeof(power_well_ids) * 8);
		WARN_ON(power_well_ids & BIT_ULL(id));
		power_well_ids |= BIT_ULL(id);
	}

	return 0;
}
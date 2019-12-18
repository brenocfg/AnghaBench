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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct smu_context {int dummy; } ;

/* Variables and functions */
 int smu_feature_get_enabled_mask (struct smu_context*,scalar_t__*,int) ; 
 int smu_feature_update_enable_state (struct smu_context*,int,int) ; 

int smu_sys_set_pp_feature_mask(struct smu_context *smu, uint64_t new_mask)
{
	int ret = 0;
	uint32_t feature_mask[2] = { 0 };
	uint64_t feature_2_enabled = 0;
	uint64_t feature_2_disabled = 0;
	uint64_t feature_enables = 0;

	ret = smu_feature_get_enabled_mask(smu, feature_mask, 2);
	if (ret)
		return ret;

	feature_enables = ((uint64_t)feature_mask[1] << 32 | (uint64_t)feature_mask[0]);

	feature_2_enabled  = ~feature_enables & new_mask;
	feature_2_disabled = feature_enables & ~new_mask;

	if (feature_2_enabled) {
		ret = smu_feature_update_enable_state(smu, feature_2_enabled, true);
		if (ret)
			return ret;
	}
	if (feature_2_disabled) {
		ret = smu_feature_update_enable_state(smu, feature_2_disabled, false);
		if (ret)
			return ret;
	}

	return ret;
}
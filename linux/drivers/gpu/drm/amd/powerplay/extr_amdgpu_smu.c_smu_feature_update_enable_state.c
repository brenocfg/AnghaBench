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
typedef  int uint32_t ;
struct smu_context {int /*<<< orphan*/  pm_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_DisableSmuFeaturesHigh ; 
 int /*<<< orphan*/  SMU_MSG_DisableSmuFeaturesLow ; 
 int /*<<< orphan*/  SMU_MSG_EnableSmuFeaturesHigh ; 
 int /*<<< orphan*/  SMU_MSG_EnableSmuFeaturesLow ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

int smu_feature_update_enable_state(struct smu_context *smu, uint64_t feature_mask, bool enabled)
{
	uint32_t feature_low = 0, feature_high = 0;
	int ret = 0;

	if (!smu->pm_enabled)
		return ret;

	feature_low = (feature_mask >> 0 ) & 0xffffffff;
	feature_high = (feature_mask >> 32) & 0xffffffff;

	if (enabled) {
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_EnableSmuFeaturesLow,
						  feature_low);
		if (ret)
			return ret;
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_EnableSmuFeaturesHigh,
						  feature_high);
		if (ret)
			return ret;

	} else {
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_DisableSmuFeaturesLow,
						  feature_low);
		if (ret)
			return ret;
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_DisableSmuFeaturesHigh,
						  feature_high);
		if (ret)
			return ret;

	}

	return ret;
}
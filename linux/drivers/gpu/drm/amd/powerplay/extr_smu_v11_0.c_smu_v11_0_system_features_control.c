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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_feature {int /*<<< orphan*/  feature_num; int /*<<< orphan*/  supported; int /*<<< orphan*/  enabled; } ;
struct smu_context {scalar_t__ pm_enabled; struct smu_feature smu_feature; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_MSG_DisableAllSmuFeatures ; 
 int /*<<< orphan*/  SMU_MSG_EnableAllSmuFeatures ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int smu_feature_get_enabled_mask (struct smu_context*,int /*<<< orphan*/ *,int) ; 
 int smu_send_smc_msg (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_system_features_control(struct smu_context *smu,
					     bool en)
{
	struct smu_feature *feature = &smu->smu_feature;
	uint32_t feature_mask[2];
	int ret = 0;

	if (smu->pm_enabled) {
		ret = smu_send_smc_msg(smu, (en ? SMU_MSG_EnableAllSmuFeatures :
					     SMU_MSG_DisableAllSmuFeatures));
		if (ret)
			return ret;
	}

	ret = smu_feature_get_enabled_mask(smu, feature_mask, 2);
	if (ret)
		return ret;

	bitmap_copy(feature->enabled, (unsigned long *)&feature_mask,
		    feature->feature_num);
	bitmap_copy(feature->supported, (unsigned long *)&feature_mask,
		    feature->feature_num);

	return ret;
}
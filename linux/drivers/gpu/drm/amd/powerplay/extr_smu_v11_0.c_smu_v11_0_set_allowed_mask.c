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
struct smu_feature {int feature_num; int /*<<< orphan*/  mutex; int /*<<< orphan*/  allowed; } ;
struct smu_context {struct smu_feature smu_feature; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_FEATURE_MAX ; 
 int /*<<< orphan*/  SMU_MSG_SetAllowedFeaturesMaskHigh ; 
 int /*<<< orphan*/  SMU_MSG_SetAllowedFeaturesMaskLow ; 
 int /*<<< orphan*/  bitmap_copy (unsigned long*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu_v11_0_set_allowed_mask(struct smu_context *smu)
{
	struct smu_feature *feature = &smu->smu_feature;
	int ret = 0;
	uint32_t feature_mask[2];

	mutex_lock(&feature->mutex);
	if (bitmap_empty(feature->allowed, SMU_FEATURE_MAX) || feature->feature_num < 64)
		goto failed;

	bitmap_copy((unsigned long *)feature_mask, feature->allowed, 64);

	ret = smu_send_smc_msg_with_param(smu, SMU_MSG_SetAllowedFeaturesMaskHigh,
					  feature_mask[1]);
	if (ret)
		goto failed;

	ret = smu_send_smc_msg_with_param(smu, SMU_MSG_SetAllowedFeaturesMaskLow,
					  feature_mask[0]);
	if (ret)
		goto failed;

failed:
	mutex_unlock(&feature->mutex);
	return ret;
}
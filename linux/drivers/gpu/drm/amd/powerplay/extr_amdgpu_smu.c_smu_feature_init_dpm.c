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
struct smu_feature {int /*<<< orphan*/  mutex; int /*<<< orphan*/  feature_num; int /*<<< orphan*/  allowed; } ;
struct smu_context {int /*<<< orphan*/  pm_enabled; struct smu_feature smu_feature; } ;

/* Variables and functions */
 int SMU_FEATURE_MAX ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_get_allowed_feature_mask (struct smu_context*,int /*<<< orphan*/ *,int) ; 

int smu_feature_init_dpm(struct smu_context *smu)
{
	struct smu_feature *feature = &smu->smu_feature;
	int ret = 0;
	uint32_t allowed_feature_mask[SMU_FEATURE_MAX/32];

	if (!smu->pm_enabled)
		return ret;
	mutex_lock(&feature->mutex);
	bitmap_zero(feature->allowed, SMU_FEATURE_MAX);
	mutex_unlock(&feature->mutex);

	ret = smu_get_allowed_feature_mask(smu, allowed_feature_mask,
					     SMU_FEATURE_MAX/32);
	if (ret)
		return ret;

	mutex_lock(&feature->mutex);
	bitmap_or(feature->allowed, feature->allowed,
		      (unsigned long *)allowed_feature_mask,
		      feature->feature_num);
	mutex_unlock(&feature->mutex);

	return ret;
}
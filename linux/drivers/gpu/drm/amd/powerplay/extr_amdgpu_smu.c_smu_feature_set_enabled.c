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
typedef  unsigned long long uint64_t ;
struct smu_feature {int feature_num; int /*<<< orphan*/  mutex; int /*<<< orphan*/  enabled; } ;
struct smu_context {struct smu_feature smu_feature; } ;
typedef  enum smu_feature_mask { ____Placeholder_smu_feature_mask } smu_feature_mask ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_feature_get_index (struct smu_context*,int) ; 
 int smu_feature_update_enable_state (struct smu_context*,unsigned long long,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

int smu_feature_set_enabled(struct smu_context *smu, enum smu_feature_mask mask,
			    bool enable)
{
	struct smu_feature *feature = &smu->smu_feature;
	int feature_id;
	uint64_t feature_mask = 0;
	int ret = 0;

	feature_id = smu_feature_get_index(smu, mask);
	if (feature_id < 0)
		return -EINVAL;

	WARN_ON(feature_id > feature->feature_num);

	feature_mask = 1ULL << feature_id;

	mutex_lock(&feature->mutex);
	ret = smu_feature_update_enable_state(smu, feature_mask, enable);
	if (ret)
		goto failed;

	if (enable)
		test_and_set_bit(feature_id, feature->enabled);
	else
		test_and_clear_bit(feature_id, feature->enabled);

failed:
	mutex_unlock(&feature->mutex);

	return ret;
}
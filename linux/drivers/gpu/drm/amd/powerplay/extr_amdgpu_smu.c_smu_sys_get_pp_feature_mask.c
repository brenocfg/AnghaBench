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
struct smu_context {int dummy; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 int SMU_FEATURE_COUNT ; 
 int smu_feature_get_enabled_mask (struct smu_context*,int*,int) ; 
 size_t smu_feature_get_index (struct smu_context*,int) ; 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int) ; 
 char* smu_get_feature_name (struct smu_context*,int) ; 
 size_t sprintf (char*,char*,int,...) ; 

size_t smu_sys_get_pp_feature_mask(struct smu_context *smu, char *buf)
{
	size_t size = 0;
	int ret = 0, i = 0;
	uint32_t feature_mask[2] = { 0 };
	int32_t feature_index = 0;
	uint32_t count = 0;
	uint32_t sort_feature[SMU_FEATURE_COUNT];
	uint64_t hw_feature_count = 0;

	ret = smu_feature_get_enabled_mask(smu, feature_mask, 2);
	if (ret)
		goto failed;

	size =  sprintf(buf + size, "features high: 0x%08x low: 0x%08x\n",
			feature_mask[1], feature_mask[0]);

	for (i = 0; i < SMU_FEATURE_COUNT; i++) {
		feature_index = smu_feature_get_index(smu, i);
		if (feature_index < 0)
			continue;
		sort_feature[feature_index] = i;
		hw_feature_count++;
	}

	for (i = 0; i < hw_feature_count; i++) {
		size += sprintf(buf + size, "%02d. %-20s (%2d) : %s\n",
			       count++,
			       smu_get_feature_name(smu, sort_feature[i]),
			       i,
			       !!smu_feature_is_enabled(smu, sort_feature[i]) ?
			       "enabled" : "disabled");
	}

failed:
	return size;
}
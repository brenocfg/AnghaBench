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
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DF_V3_6_MAX_COUNTERS ; 
 int /*<<< orphan*/  PERF_TYPE_AMDGPU_DF ; 
 int /*<<< orphan*/  df_v3_6_attr_groups ; 
 int init_pmu_by_type (struct amdgpu_device*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int amdgpu_pmu_init(struct amdgpu_device *adev)
{
	int ret = 0;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
		/* init df */
		ret = init_pmu_by_type(adev, df_v3_6_attr_groups,
				       "DF", "amdgpu_df", PERF_TYPE_AMDGPU_DF,
				       DF_V3_6_MAX_COUNTERS);

		/* other pmu types go here*/
		break;
	default:
		return 0;
	}

	return 0;
}
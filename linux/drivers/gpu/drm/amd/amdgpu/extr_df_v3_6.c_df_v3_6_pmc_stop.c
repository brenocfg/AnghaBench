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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  df_v3_6_perfmon_wreg (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int df_v3_6_pmc_get_ctrl_settings (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  df_v3_6_pmc_release_cntr (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int df_v3_6_pmc_stop(struct amdgpu_device *adev, uint64_t config,
			    int is_disable)
{
	uint32_t lo_base_addr, hi_base_addr, lo_val, hi_val;
	int ret = 0;

	switch (adev->asic_type) {
	case CHIP_VEGA20:
		ret = df_v3_6_pmc_get_ctrl_settings(adev,
			config,
			&lo_base_addr,
			&hi_base_addr,
			&lo_val,
			&hi_val);

		if (ret)
			return ret;

		df_v3_6_perfmon_wreg(adev, lo_base_addr, 0, hi_base_addr, 0);

		if (is_disable)
			df_v3_6_pmc_release_cntr(adev, config);

		break;
	default:
		break;
	}

	return ret;
}
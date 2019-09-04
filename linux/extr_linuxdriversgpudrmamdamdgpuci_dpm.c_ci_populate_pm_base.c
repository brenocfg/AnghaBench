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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ci_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  smc_powertune_table; scalar_t__ caps_power_containment; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  SMU7_Discrete_PmFuses ;

/* Variables and functions */
 int /*<<< orphan*/  PmFuseTable ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU7_Firmware_Header ; 
 int amdgpu_ci_copy_bytes_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int amdgpu_ci_read_smc_sram_dword (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_min_max_v_gnbl_pm_lid_from_bapm_vddc (struct amdgpu_device*) ; 
 int ci_populate_bapm_vddc_base_leakage_sidd (struct amdgpu_device*) ; 
 int ci_populate_bapm_vddc_vid_sidd (struct amdgpu_device*) ; 
 int ci_populate_dw8 (struct amdgpu_device*) ; 
 int ci_populate_fuzzy_fan (struct amdgpu_device*) ; 
 int ci_populate_svi_load_line (struct amdgpu_device*) ; 
 int ci_populate_tdc_limit (struct amdgpu_device*) ; 
 int ci_populate_vddc_vid (struct amdgpu_device*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_populate_pm_base(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 pm_fuse_table_offset;
	int ret;

	if (pi->caps_power_containment) {
		ret = amdgpu_ci_read_smc_sram_dword(adev,
					     SMU7_FIRMWARE_HEADER_LOCATION +
					     offsetof(SMU7_Firmware_Header, PmFuseTable),
					     &pm_fuse_table_offset, pi->sram_end);
		if (ret)
			return ret;
		ret = ci_populate_bapm_vddc_vid_sidd(adev);
		if (ret)
			return ret;
		ret = ci_populate_vddc_vid(adev);
		if (ret)
			return ret;
		ret = ci_populate_svi_load_line(adev);
		if (ret)
			return ret;
		ret = ci_populate_tdc_limit(adev);
		if (ret)
			return ret;
		ret = ci_populate_dw8(adev);
		if (ret)
			return ret;
		ret = ci_populate_fuzzy_fan(adev);
		if (ret)
			return ret;
		ret = ci_min_max_v_gnbl_pm_lid_from_bapm_vddc(adev);
		if (ret)
			return ret;
		ret = ci_populate_bapm_vddc_base_leakage_sidd(adev);
		if (ret)
			return ret;
		ret = amdgpu_ci_copy_bytes_to_smc(adev, pm_fuse_table_offset,
					   (u8 *)&pi->smc_powertune_table,
					   sizeof(SMU7_Discrete_PmFuses), pi->sram_end);
		if (ret)
			return ret;
	}

	return 0;
}
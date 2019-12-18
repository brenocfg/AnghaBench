#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {int dummy; } ;
struct kv_power_info {scalar_t__ vce_power_gated; scalar_t__ uvd_power_gated; TYPE_1__* graphics_level; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  SclkFrequency; } ;

/* Variables and functions */
 size_t RREG32_SMC (int /*<<< orphan*/ ) ; 
 size_t SMU_VOLTAGE_STATUS__SMU_VOLTAGE_CURRENT_LEVEL_MASK ; 
 size_t SMU_VOLTAGE_STATUS__SMU_VOLTAGE_CURRENT_LEVEL__SHIFT ; 
 size_t SMU__NUM_SCLK_DPM_STATE ; 
 size_t TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK ; 
 size_t TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSMU_VOLTAGE_STATUS ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  kv_convert_8bit_index_to_voltage (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void
kv_dpm_debugfs_print_current_performance_level(void *handle,
					       struct seq_file *m)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 current_index =
		(RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX) &
		TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK) >>
		TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT;
	u32 sclk, tmp;
	u16 vddc;

	if (current_index >= SMU__NUM_SCLK_DPM_STATE) {
		seq_printf(m, "invalid dpm profile %d\n", current_index);
	} else {
		sclk = be32_to_cpu(pi->graphics_level[current_index].SclkFrequency);
		tmp = (RREG32_SMC(ixSMU_VOLTAGE_STATUS) &
			SMU_VOLTAGE_STATUS__SMU_VOLTAGE_CURRENT_LEVEL_MASK) >>
			SMU_VOLTAGE_STATUS__SMU_VOLTAGE_CURRENT_LEVEL__SHIFT;
		vddc = kv_convert_8bit_index_to_voltage(adev, (u16)tmp);
		seq_printf(m, "uvd    %sabled\n", pi->uvd_power_gated ? "dis" : "en");
		seq_printf(m, "vce    %sabled\n", pi->vce_power_gated ? "dis" : "en");
		seq_printf(m, "power level %d    sclk: %u vddc: %u\n",
			   current_index, sclk, vddc);
	}
}
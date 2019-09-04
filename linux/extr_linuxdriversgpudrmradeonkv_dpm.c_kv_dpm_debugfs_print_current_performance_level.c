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
struct radeon_device {int dummy; } ;
struct kv_power_info {scalar_t__ vce_power_gated; scalar_t__ uvd_power_gated; TYPE_1__* graphics_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  SclkFrequency; } ;

/* Variables and functions */
 size_t CURR_SCLK_INDEX_MASK ; 
 size_t CURR_SCLK_INDEX_SHIFT ; 
 size_t RREG32_SMC (int /*<<< orphan*/ ) ; 
 size_t SMU_VOLTAGE_CURRENT_LEVEL_MASK ; 
 size_t SMU_VOLTAGE_CURRENT_LEVEL_SHIFT ; 
 int /*<<< orphan*/  SMU_VOLTAGE_STATUS ; 
 size_t SMU__NUM_SCLK_DPM_STATE ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_convert_8bit_index_to_voltage (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

void kv_dpm_debugfs_print_current_performance_level(struct radeon_device *rdev,
						    struct seq_file *m)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 current_index =
		(RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX) & CURR_SCLK_INDEX_MASK) >>
		CURR_SCLK_INDEX_SHIFT;
	u32 sclk, tmp;
	u16 vddc;

	if (current_index >= SMU__NUM_SCLK_DPM_STATE) {
		seq_printf(m, "invalid dpm profile %d\n", current_index);
	} else {
		sclk = be32_to_cpu(pi->graphics_level[current_index].SclkFrequency);
		tmp = (RREG32_SMC(SMU_VOLTAGE_STATUS) & SMU_VOLTAGE_CURRENT_LEVEL_MASK) >>
			SMU_VOLTAGE_CURRENT_LEVEL_SHIFT;
		vddc = kv_convert_8bit_index_to_voltage(rdev, (u16)tmp);
		seq_printf(m, "uvd    %sabled\n", pi->uvd_power_gated ? "dis" : "en");
		seq_printf(m, "vce    %sabled\n", pi->vce_power_gated ? "dis" : "en");
		seq_printf(m, "power level %d    sclk: %u vddc: %u\n",
			   current_index, sclk, vddc);
	}
}
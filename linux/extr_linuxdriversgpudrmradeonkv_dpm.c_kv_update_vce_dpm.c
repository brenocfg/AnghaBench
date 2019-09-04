#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct radeon_vce_clock_voltage_dependency_table {int count; } ;
struct radeon_ps {scalar_t__ evclk; } ;
struct TYPE_4__ {struct radeon_vce_clock_voltage_dependency_table vce_clock_voltage_dependency_table; } ;
struct TYPE_5__ {TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct kv_power_info {int vce_boot_level; scalar_t__ caps_stable_p_state; int /*<<< orphan*/  sram_end; scalar_t__ dpm_table_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_SetEnabledMask ; 
 int /*<<< orphan*/  RADEON_CG_BLOCK_VCE ; 
 int /*<<< orphan*/  SMU7_Fusion_DpmTable ; 
 int /*<<< orphan*/  VceBootLevel ; 
 int /*<<< orphan*/  cik_update_cg (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int kv_copy_bytes_to_smc (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_dpm_powergate_vce (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_vce_dpm (struct radeon_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int kv_get_vce_boot_level (struct radeon_device*,scalar_t__) ; 
 int /*<<< orphan*/  kv_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_update_vce_dpm(struct radeon_device *rdev,
			     struct radeon_ps *radeon_new_state,
			     struct radeon_ps *radeon_current_state)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	struct radeon_vce_clock_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table;
	int ret;

	if (radeon_new_state->evclk > 0 && radeon_current_state->evclk == 0) {
		kv_dpm_powergate_vce(rdev, false);
		/* turn the clocks on when encoding */
		cik_update_cg(rdev, RADEON_CG_BLOCK_VCE, false);
		if (pi->caps_stable_p_state)
			pi->vce_boot_level = table->count - 1;
		else
			pi->vce_boot_level = kv_get_vce_boot_level(rdev, radeon_new_state->evclk);

		ret = kv_copy_bytes_to_smc(rdev,
					   pi->dpm_table_start +
					   offsetof(SMU7_Fusion_DpmTable, VceBootLevel),
					   (u8 *)&pi->vce_boot_level,
					   sizeof(u8),
					   pi->sram_end);
		if (ret)
			return ret;

		if (pi->caps_stable_p_state)
			kv_send_msg_to_smc_with_parameter(rdev,
							  PPSMC_MSG_VCEDPM_SetEnabledMask,
							  (1 << pi->vce_boot_level));

		kv_enable_vce_dpm(rdev, true);
	} else if (radeon_new_state->evclk == 0 && radeon_current_state->evclk > 0) {
		kv_enable_vce_dpm(rdev, false);
		/* turn the clocks off when not encoding */
		cik_update_cg(rdev, RADEON_CG_BLOCK_VCE, true);
		kv_dpm_powergate_vce(rdev, true);
	}

	return 0;
}
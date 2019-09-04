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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct radeon_uvd_clock_voltage_dependency_table {int count; } ;
struct TYPE_4__ {struct radeon_uvd_clock_voltage_dependency_table uvd_clock_voltage_dependency_table; } ;
struct TYPE_5__ {TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct kv_power_info {int uvd_boot_level; int /*<<< orphan*/  sram_end; scalar_t__ dpm_table_start; scalar_t__ caps_stable_p_state; int /*<<< orphan*/  caps_uvd_dpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_UVDDPM_SetEnabledMask ; 
 int /*<<< orphan*/  SMU7_Fusion_DpmTable ; 
 int /*<<< orphan*/  UvdBootLevel ; 
 int kv_copy_bytes_to_smc (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int kv_enable_uvd_dpm (struct radeon_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_update_uvd_dpm(struct radeon_device *rdev, bool gate)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	struct radeon_uvd_clock_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table;
	int ret;
	u32 mask;

	if (!gate) {
		if (table->count)
			pi->uvd_boot_level = table->count - 1;
		else
			pi->uvd_boot_level = 0;

		if (!pi->caps_uvd_dpm || pi->caps_stable_p_state) {
			mask = 1 << pi->uvd_boot_level;
		} else {
			mask = 0x1f;
		}

		ret = kv_copy_bytes_to_smc(rdev,
					   pi->dpm_table_start +
					   offsetof(SMU7_Fusion_DpmTable, UvdBootLevel),
					   (uint8_t *)&pi->uvd_boot_level,
					   sizeof(u8), pi->sram_end);
		if (ret)
			return ret;

		kv_send_msg_to_smc_with_parameter(rdev,
						  PPSMC_MSG_UVDDPM_SetEnabledMask,
						  mask);
	}

	return kv_enable_uvd_dpm(rdev, !gate);
}
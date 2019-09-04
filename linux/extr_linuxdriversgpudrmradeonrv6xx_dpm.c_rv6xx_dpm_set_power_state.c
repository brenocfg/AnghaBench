#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rv6xx_power_info {scalar_t__ thermal_protection; scalar_t__ dynamic_pcie_gen2; scalar_t__ voltage_control; scalar_t__ restricted_levels; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {int platform_caps; int voltage_response_time; struct radeon_ps* current_ps; struct radeon_ps* requested_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_BACKBIAS ; 
 int ATOM_PP_PLATFORM_CAP_STEPVDDC ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_HIGH ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_LOW ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  r600_enable_thermal_protection (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_power_level_enable (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_set_at (struct radeon_device*,int,int,int,int) ; 
 int /*<<< orphan*/  r600_wait_for_power_level (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_wait_for_power_level_unequal (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv6xx_calculate_stepping_parameters (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_clear_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_enable_dynamic_backbias_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_dynamic_pcie_gen2 (struct radeon_device*,struct radeon_ps*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_dynamic_voltage_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_high (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_enable_medium (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_enable_thermal_protection (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_generate_low_step (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_generate_stepping_table (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_generate_transition_stepping (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_invalidate_intermediate_steps (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_at (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_high (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_low (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_low_to_lowest_state (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_medium (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_medium_for_transition (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_stepping_parameters_except_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_stepping_parameters_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_reset_lvtm_data_sync (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_set_safe_backbias (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_set_safe_pcie_gen2 (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_set_sw_voltage_to_low (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_set_sw_voltage_to_safe (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int rv6xx_step_voltage_if_decreasing (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_step_voltage_if_increasing (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 

int rv6xx_dpm_set_power_state(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	struct radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	struct radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	int ret;

	pi->restricted_levels = 0;

	rv6xx_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);

	rv6xx_clear_vc(rdev);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_set_at(rdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);

	if (pi->thermal_protection)
		r600_enable_thermal_protection(rdev, false);

	r600_wait_for_power_level(rdev, R600_POWER_LEVEL_LOW);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);

	rv6xx_generate_transition_stepping(rdev, new_ps, old_ps);
	rv6xx_program_power_level_medium_for_transition(rdev);

	if (pi->voltage_control) {
		rv6xx_set_sw_voltage_to_safe(rdev, new_ps, old_ps);
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
			rv6xx_set_sw_voltage_to_low(rdev, old_ps);
	}

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_set_safe_backbias(rdev, new_ps, old_ps);

	if (pi->dynamic_pcie_gen2)
		rv6xx_set_safe_pcie_gen2(rdev, new_ps, old_ps);

	if (pi->voltage_control)
		rv6xx_enable_dynamic_voltage_control(rdev, false);

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_dynamic_backbias_control(rdev, false);

	if (pi->voltage_control) {
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
			rv6xx_step_voltage_if_increasing(rdev, new_ps, old_ps);
		msleep((rdev->pm.dpm.voltage_response_time + 999) / 1000);
	}

	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, false);
	r600_wait_for_power_level_unequal(rdev, R600_POWER_LEVEL_LOW);

	rv6xx_generate_low_step(rdev, new_ps);
	rv6xx_invalidate_intermediate_steps(rdev);
	rv6xx_calculate_stepping_parameters(rdev, new_ps);
	rv6xx_program_stepping_parameters_lowest_entry(rdev);
	rv6xx_program_power_level_low_to_lowest_state(rdev);

	r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_wait_for_power_level(rdev, R600_POWER_LEVEL_LOW);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);

	if (pi->voltage_control) {
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC) {
			ret = rv6xx_step_voltage_if_decreasing(rdev, new_ps, old_ps);
			if (ret)
				return ret;
		}
		rv6xx_enable_dynamic_voltage_control(rdev, true);
	}

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_dynamic_backbias_control(rdev, true);

	if (pi->dynamic_pcie_gen2)
		rv6xx_enable_dynamic_pcie_gen2(rdev, new_ps, true);

	rv6xx_reset_lvtm_data_sync(rdev);

	rv6xx_generate_stepping_table(rdev, new_ps);
	rv6xx_program_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_power_level_low(rdev);
	rv6xx_program_power_level_medium(rdev);
	rv6xx_program_power_level_high(rdev);
	rv6xx_enable_medium(rdev);
	rv6xx_enable_high(rdev);

	if (pi->thermal_protection)
		rv6xx_enable_thermal_protection(rdev, true);
	rv6xx_program_vc(rdev);
	rv6xx_program_at(rdev);

	rv6xx_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);

	return 0;
}
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
struct rv6xx_power_info {int display_gap; scalar_t__ gfx_clock_gating; scalar_t__ dynamic_pcie_gen2; scalar_t__ voltage_control; scalar_t__ dynamic_ss; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {int platform_caps; struct radeon_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_BACKBIAS ; 
 int EINVAL ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_HIGH ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_LOW ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 scalar_t__ r600_dynamicpm_enabled (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_gfx_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_power_level_enable (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_start_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_calculate_stepping_parameters (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv6xx_enable_auto_throttle_source (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv6xx_enable_backbias (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_display_gap (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_dynamic_pcie_gen2 (struct radeon_device*,struct radeon_ps*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_spread_spectrum (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_static_voltage_control (struct radeon_device*,struct radeon_ps*,int) ; 
 int /*<<< orphan*/  rv6xx_generate_stepping_table (struct radeon_device*,struct radeon_ps*) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_at (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_bsp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_engine_speed_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_fcp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_git (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_mpll_timing_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_enter_state (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_high (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_low (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_power_level_medium (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_sstp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_stepping_parameters_except_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_stepping_parameters_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_tp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_tpp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_vddc3d_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_voltage_gpio_pins (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_voltage_timing_parameters (struct radeon_device*) ; 

int rv6xx_dpm_enable(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	if (r600_dynamicpm_enabled(rdev))
		return -EINVAL;

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_backbias(rdev, true);

	if (pi->dynamic_ss)
		rv6xx_enable_spread_spectrum(rdev, true);

	rv6xx_program_mpll_timing_parameters(rdev);
	rv6xx_program_bsp(rdev);
	rv6xx_program_git(rdev);
	rv6xx_program_tp(rdev);
	rv6xx_program_tpp(rdev);
	rv6xx_program_sstp(rdev);
	rv6xx_program_fcp(rdev);
	rv6xx_program_vddc3d_parameters(rdev);
	rv6xx_program_voltage_timing_parameters(rdev);
	rv6xx_program_engine_speed_parameters(rdev);

	rv6xx_enable_display_gap(rdev, true);
	if (pi->display_gap == false)
		rv6xx_enable_display_gap(rdev, false);

	rv6xx_program_power_level_enter_state(rdev);

	rv6xx_calculate_stepping_parameters(rdev, boot_ps);

	if (pi->voltage_control)
		rv6xx_program_voltage_gpio_pins(rdev);

	rv6xx_generate_stepping_table(rdev, boot_ps);

	rv6xx_program_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_stepping_parameters_lowest_entry(rdev);

	rv6xx_program_power_level_low(rdev);
	rv6xx_program_power_level_medium(rdev);
	rv6xx_program_power_level_high(rdev);
	rv6xx_program_vc(rdev);
	rv6xx_program_at(rdev);

	r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_HIGH, true);

	rv6xx_enable_auto_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	r600_start_dpm(rdev);

	if (pi->voltage_control)
		rv6xx_enable_static_voltage_control(rdev, boot_ps, false);

	if (pi->dynamic_pcie_gen2)
		rv6xx_enable_dynamic_pcie_gen2(rdev, boot_ps, true);

	if (pi->gfx_clock_gating)
		r600_gfx_clockgating_enable(rdev, true);

	return 0;
}
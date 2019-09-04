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
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct igp_power_info {scalar_t__ gfx_clock_gating; scalar_t__ voltage_control; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ r600_dynamicpm_enabled (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_gfx_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rs780_clk_scaling_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rs780_disable_vbios_powersaving (struct radeon_device*) ; 
 struct igp_power_info* rs780_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_get_pm_mode_parameters (struct radeon_device*) ; 
 int rs780_initialize_dpm_parameters (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rs780_preset_ranges_slow_clk_fbdiv_en (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_preset_starting_fbdiv (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_program_at (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_set_engine_clock_sc (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_set_engine_clock_ssc (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_set_engine_clock_tdc (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_set_engine_clock_wfc (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_start_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_voltage_scaling_init (struct radeon_device*) ; 

int rs780_dpm_enable(struct radeon_device *rdev)
{
	struct igp_power_info *pi = rs780_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	int ret;

	rs780_get_pm_mode_parameters(rdev);
	rs780_disable_vbios_powersaving(rdev);

	if (r600_dynamicpm_enabled(rdev))
		return -EINVAL;
	ret = rs780_initialize_dpm_parameters(rdev, boot_ps);
	if (ret)
		return ret;
	rs780_start_dpm(rdev);

	rs780_preset_ranges_slow_clk_fbdiv_en(rdev);
	rs780_preset_starting_fbdiv(rdev);
	if (pi->voltage_control)
		rs780_voltage_scaling_init(rdev);
	rs780_clk_scaling_enable(rdev, true);
	rs780_set_engine_clock_sc(rdev);
	rs780_set_engine_clock_wfc(rdev);
	rs780_program_at(rdev);
	rs780_set_engine_clock_tdc(rdev);
	rs780_set_engine_clock_ssc(rdev);

	if (pi->gfx_clock_gating)
		r600_gfx_clockgating_enable(rdev, true);

	return 0;
}
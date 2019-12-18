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
struct TYPE_4__ {struct radeon_ps* current_ps; struct radeon_ps* requested_ps; } ;
struct TYPE_3__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_1__ pm; } ;
struct igp_power_info {scalar_t__ voltage_control; int /*<<< orphan*/  max_voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rs780_activate_engine_clk_scaling (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rs780_enable_voltage_scaling (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rs780_force_voltage (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct igp_power_info* rs780_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rs780_get_pm_mode_parameters (struct radeon_device*) ; 
 int rs780_set_engine_clock_scaling (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rs780_set_engine_clock_spc (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rs780_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rs780_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 

int rs780_dpm_set_power_state(struct radeon_device *rdev)
{
	struct igp_power_info *pi = rs780_get_pi(rdev);
	struct radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	struct radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	int ret;

	rs780_get_pm_mode_parameters(rdev);

	rs780_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);

	if (pi->voltage_control) {
		rs780_force_voltage(rdev, pi->max_voltage);
		mdelay(5);
	}

	ret = rs780_set_engine_clock_scaling(rdev, new_ps, old_ps);
	if (ret)
		return ret;
	rs780_set_engine_clock_spc(rdev, new_ps, old_ps);

	rs780_activate_engine_clk_scaling(rdev, new_ps, old_ps);

	if (pi->voltage_control)
		rs780_enable_voltage_scaling(rdev, new_ps);

	rs780_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);

	return 0;
}
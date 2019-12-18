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
struct trinity_power_info {scalar_t__ enable_bapm; scalar_t__ enable_dpm; struct radeon_ps current_rps; struct radeon_ps requested_rps; } ;
struct TYPE_3__ {int /*<<< orphan*/  ac_power; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  trinity_acquire_mutex (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_dpm_bapm_enable (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_enable_power_level_0 (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_force_level_0 (struct radeon_device*) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_program_power_levels_0_to_n (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_release_mutex (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_set_vce_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_setup_nbp_sim (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_unforce_levels (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_wait_for_level_0 (struct radeon_device*) ; 

int trinity_dpm_set_power_state(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	struct radeon_ps *new_ps = &pi->requested_rps;
	struct radeon_ps *old_ps = &pi->current_rps;

	trinity_acquire_mutex(rdev);
	if (pi->enable_dpm) {
		if (pi->enable_bapm)
			trinity_dpm_bapm_enable(rdev, rdev->pm.dpm.ac_power);
		trinity_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);
		trinity_enable_power_level_0(rdev);
		trinity_force_level_0(rdev);
		trinity_wait_for_level_0(rdev);
		trinity_setup_nbp_sim(rdev, new_ps);
		trinity_program_power_levels_0_to_n(rdev, new_ps, old_ps);
		trinity_force_level_0(rdev);
		trinity_unforce_levels(rdev);
		trinity_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);
		trinity_set_vce_clock(rdev, new_ps, old_ps);
	}
	trinity_release_mutex(rdev);

	return 0;
}
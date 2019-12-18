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
struct radeon_ps {int dummy; } ;
struct sumo_power_info {scalar_t__ enable_dpm; scalar_t__ enable_boost; struct radeon_ps current_rps; struct radeon_ps requested_rps; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sumo_enable_boost (struct radeon_device*,struct radeon_ps*,int) ; 
 int /*<<< orphan*/  sumo_enable_power_level_0 (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_force_nbp_state (struct radeon_device*,struct radeon_ps*) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_patch_boost_state (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_post_notify_alt_vddnb_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_pre_notify_alt_vddnb_change (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_program_at (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_program_bsp (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_program_power_levels_0_to_n (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_program_wl (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_set_forced_level_0 (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_set_forced_mode_disabled (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_set_forced_mode_enabled (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_wait_for_level_0 (struct radeon_device*) ; 

int sumo_dpm_set_power_state(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct radeon_ps *new_ps = &pi->requested_rps;
	struct radeon_ps *old_ps = &pi->current_rps;

	if (pi->enable_dpm)
		sumo_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);
	if (pi->enable_boost) {
		sumo_enable_boost(rdev, new_ps, false);
		sumo_patch_boost_state(rdev, new_ps);
	}
	if (pi->enable_dpm) {
		sumo_pre_notify_alt_vddnb_change(rdev, new_ps, old_ps);
		sumo_enable_power_level_0(rdev);
		sumo_set_forced_level_0(rdev);
		sumo_set_forced_mode_enabled(rdev);
		sumo_wait_for_level_0(rdev);
		sumo_program_power_levels_0_to_n(rdev, new_ps, old_ps);
		sumo_program_wl(rdev, new_ps);
		sumo_program_bsp(rdev, new_ps);
		sumo_program_at(rdev, new_ps);
		sumo_force_nbp_state(rdev, new_ps);
		sumo_set_forced_mode_disabled(rdev);
		sumo_set_forced_mode_enabled(rdev);
		sumo_set_forced_mode_disabled(rdev);
		sumo_post_notify_alt_vddnb_change(rdev, new_ps, old_ps);
	}
	if (pi->enable_boost)
		sumo_enable_boost(rdev, new_ps, true);
	if (pi->enable_dpm)
		sumo_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);

	return 0;
}
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
struct TYPE_4__ {int profile; size_t profile_index; int active_crtc_count; TYPE_1__* profiles; int /*<<< orphan*/  requested_clock_mode_index; int /*<<< orphan*/  requested_power_state_index; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct TYPE_3__ {int /*<<< orphan*/  dpms_on_cm_idx; int /*<<< orphan*/  dpms_on_ps_idx; int /*<<< orphan*/  dpms_off_cm_idx; int /*<<< orphan*/  dpms_off_ps_idx; } ;

/* Variables and functions */
#define  PM_PROFILE_AUTO 132 
#define  PM_PROFILE_DEFAULT 131 
 size_t PM_PROFILE_DEFAULT_IDX ; 
#define  PM_PROFILE_HIGH 130 
 void* PM_PROFILE_HIGH_MH_IDX ; 
 void* PM_PROFILE_HIGH_SH_IDX ; 
#define  PM_PROFILE_LOW 129 
 size_t PM_PROFILE_LOW_MH_IDX ; 
 size_t PM_PROFILE_LOW_SH_IDX ; 
#define  PM_PROFILE_MID 128 
 void* PM_PROFILE_MID_MH_IDX ; 
 void* PM_PROFILE_MID_SH_IDX ; 
 int /*<<< orphan*/  power_supply_is_system_supplied () ; 

__attribute__((used)) static void radeon_pm_update_profile(struct radeon_device *rdev)
{
	switch (rdev->pm.profile) {
	case PM_PROFILE_DEFAULT:
		rdev->pm.profile_index = PM_PROFILE_DEFAULT_IDX;
		break;
	case PM_PROFILE_AUTO:
		if (power_supply_is_system_supplied() > 0) {
			if (rdev->pm.active_crtc_count > 1)
				rdev->pm.profile_index = PM_PROFILE_HIGH_MH_IDX;
			else
				rdev->pm.profile_index = PM_PROFILE_HIGH_SH_IDX;
		} else {
			if (rdev->pm.active_crtc_count > 1)
				rdev->pm.profile_index = PM_PROFILE_MID_MH_IDX;
			else
				rdev->pm.profile_index = PM_PROFILE_MID_SH_IDX;
		}
		break;
	case PM_PROFILE_LOW:
		if (rdev->pm.active_crtc_count > 1)
			rdev->pm.profile_index = PM_PROFILE_LOW_MH_IDX;
		else
			rdev->pm.profile_index = PM_PROFILE_LOW_SH_IDX;
		break;
	case PM_PROFILE_MID:
		if (rdev->pm.active_crtc_count > 1)
			rdev->pm.profile_index = PM_PROFILE_MID_MH_IDX;
		else
			rdev->pm.profile_index = PM_PROFILE_MID_SH_IDX;
		break;
	case PM_PROFILE_HIGH:
		if (rdev->pm.active_crtc_count > 1)
			rdev->pm.profile_index = PM_PROFILE_HIGH_MH_IDX;
		else
			rdev->pm.profile_index = PM_PROFILE_HIGH_SH_IDX;
		break;
	}

	if (rdev->pm.active_crtc_count == 0) {
		rdev->pm.requested_power_state_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_off_ps_idx;
		rdev->pm.requested_clock_mode_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_off_cm_idx;
	} else {
		rdev->pm.requested_power_state_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_on_ps_idx;
		rdev->pm.requested_clock_mode_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_on_cm_idx;
	}
}
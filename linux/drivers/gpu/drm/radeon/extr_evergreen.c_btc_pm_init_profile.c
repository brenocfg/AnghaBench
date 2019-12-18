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
struct TYPE_4__ {int default_power_state_index; TYPE_1__* profiles; } ;
struct radeon_device {int flags; TYPE_2__ pm; } ;
struct TYPE_3__ {int dpms_off_ps_idx; int dpms_on_ps_idx; int dpms_on_cm_idx; scalar_t__ dpms_off_cm_idx; } ;

/* Variables and functions */
 size_t PM_PROFILE_DEFAULT_IDX ; 
 size_t PM_PROFILE_HIGH_MH_IDX ; 
 size_t PM_PROFILE_HIGH_SH_IDX ; 
 size_t PM_PROFILE_LOW_MH_IDX ; 
 size_t PM_PROFILE_LOW_SH_IDX ; 
 size_t PM_PROFILE_MID_MH_IDX ; 
 size_t PM_PROFILE_MID_SH_IDX ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_BATTERY ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_PERFORMANCE ; 
 int RADEON_IS_MOBILITY ; 
 int radeon_pm_get_type_index (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btc_pm_init_profile(struct radeon_device *rdev)
{
	int idx;

	/* default */
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.default_power_state_index;
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.default_power_state_index;
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_DEFAULT_IDX].dpms_on_cm_idx = 2;
	/* starting with BTC, there is one state that is used for both
	 * MH and SH.  Difference is that we always use the high clock index for
	 * mclk.
	 */
	if (rdev->flags & RADEON_IS_MOBILITY)
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_BATTERY, 0);
	else
		idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);
	/* low sh */
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_LOW_SH_IDX].dpms_on_cm_idx = 0;
	/* mid sh */
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_MID_SH_IDX].dpms_on_cm_idx = 1;
	/* high sh */
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_HIGH_SH_IDX].dpms_on_cm_idx = 2;
	/* low mh */
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_LOW_MH_IDX].dpms_on_cm_idx = 0;
	/* mid mh */
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_MID_MH_IDX].dpms_on_cm_idx = 1;
	/* high mh */
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_off_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_on_ps_idx = idx;
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROFILE_HIGH_MH_IDX].dpms_on_cm_idx = 2;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sd; scalar_t__ hd; int uvd_active; int state; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; TYPE_3__ dpm; } ;
struct radeon_device {TYPE_4__ pm; TYPE_2__* asic; } ;
typedef  enum radeon_pm_state_type { ____Placeholder_radeon_pm_state_type } radeon_pm_state_type ;
struct TYPE_5__ {scalar_t__ powergate_uvd; } ;
struct TYPE_6__ {TYPE_1__ dpm; } ;

/* Variables and functions */
 int POWER_STATE_TYPE_INTERNAL_UVD ; 
 int POWER_STATE_TYPE_INTERNAL_UVD_HD ; 
 int POWER_STATE_TYPE_INTERNAL_UVD_HD2 ; 
 int POWER_STATE_TYPE_INTERNAL_UVD_SD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_dpm_powergate_uvd (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 

void radeon_dpm_enable_uvd(struct radeon_device *rdev, bool enable)
{
	enum radeon_pm_state_type dpm_state;

	if (rdev->asic->dpm.powergate_uvd) {
		mutex_lock(&rdev->pm.mutex);
		/* don't powergate anything if we
		   have active but pause streams */
		enable |= rdev->pm.dpm.sd > 0;
		enable |= rdev->pm.dpm.hd > 0;
		/* enable/disable UVD */
		radeon_dpm_powergate_uvd(rdev, !enable);
		mutex_unlock(&rdev->pm.mutex);
	} else {
		if (enable) {
			mutex_lock(&rdev->pm.mutex);
			rdev->pm.dpm.uvd_active = true;
			/* disable this for now */
#if 0
			if ((rdev->pm.dpm.sd == 1) && (rdev->pm.dpm.hd == 0))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_SD;
			else if ((rdev->pm.dpm.sd == 2) && (rdev->pm.dpm.hd == 0))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
			else if ((rdev->pm.dpm.sd == 0) && (rdev->pm.dpm.hd == 1))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
			else if ((rdev->pm.dpm.sd == 0) && (rdev->pm.dpm.hd == 2))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD2;
			else
#endif
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD;
			rdev->pm.dpm.state = dpm_state;
			mutex_unlock(&rdev->pm.mutex);
		} else {
			mutex_lock(&rdev->pm.mutex);
			rdev->pm.dpm.uvd_active = false;
			mutex_unlock(&rdev->pm.mutex);
		}

		radeon_pm_compute_clocks(rdev);
	}
}
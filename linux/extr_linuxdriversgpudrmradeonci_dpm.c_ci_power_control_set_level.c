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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {struct radeon_cac_tdp_table* cac_tdp_table; } ;
struct TYPE_5__ {int tdp_adjustment; TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct radeon_cac_tdp_table {scalar_t__ configurable_tdp; } ;
struct ci_power_info {scalar_t__ caps_power_containment; } ;
typedef  int s32 ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_set_overdrive_target_tdp (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_power_control_set_level(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_cac_tdp_table *cac_tdp_table =
		rdev->pm.dpm.dyn_state.cac_tdp_table;
	s32 adjust_percent;
	s32 target_tdp;
	int ret = 0;
	bool adjust_polarity = false; /* ??? */

	if (pi->caps_power_containment) {
		adjust_percent = adjust_polarity ?
			rdev->pm.dpm.tdp_adjustment : (-1 * rdev->pm.dpm.tdp_adjustment);
		target_tdp = ((100 + adjust_percent) *
			      (s32)cac_tdp_table->configurable_tdp) / 100;

		ret = ci_set_overdrive_target_tdp(rdev, (u32)target_tdp);
	}

	return ret;
}
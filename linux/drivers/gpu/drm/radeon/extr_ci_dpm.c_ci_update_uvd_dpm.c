#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {scalar_t__ count; } ;
struct TYPE_6__ {TYPE_5__ uvd_clock_voltage_dependency_table; } ;
struct TYPE_7__ {TYPE_1__ dyn_state; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_9__ {scalar_t__ UvdBootLevel; } ;
struct ci_power_info {TYPE_4__ smc_state_table; scalar_t__ caps_uvd_dpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_TABLE_475 ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UvdBootLevel (scalar_t__) ; 
 int /*<<< orphan*/  UvdBootLevel_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ci_enable_uvd_dpm (struct radeon_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_update_uvd_dpm(struct radeon_device *rdev, bool gate)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp;

	if (!gate) {
		if (pi->caps_uvd_dpm ||
		    (rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.count <= 0))
			pi->smc_state_table.UvdBootLevel = 0;
		else
			pi->smc_state_table.UvdBootLevel =
				rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.count - 1;

		tmp = RREG32_SMC(DPM_TABLE_475);
		tmp &= ~UvdBootLevel_MASK;
		tmp |= UvdBootLevel(pi->smc_state_table.UvdBootLevel);
		WREG32_SMC(DPM_TABLE_475, tmp);
	}

	return ci_enable_uvd_dpm(rdev, !gate);
}
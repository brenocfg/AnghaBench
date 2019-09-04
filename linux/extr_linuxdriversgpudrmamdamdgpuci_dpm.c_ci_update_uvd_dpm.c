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
typedef  int u32 ;
struct TYPE_10__ {int UvdBootLevel; } ;
struct ci_power_info {TYPE_5__ smc_state_table; scalar_t__ caps_uvd_dpm; } ;
struct TYPE_6__ {scalar_t__ count; } ;
struct TYPE_7__ {TYPE_1__ uvd_clock_voltage_dependency_table; } ;
struct TYPE_8__ {TYPE_2__ dyn_state; } ;
struct TYPE_9__ {TYPE_3__ dpm; } ;
struct amdgpu_device {TYPE_4__ pm; } ;

/* Variables and functions */
 int DPM_TABLE_475__UvdBootLevel_MASK ; 
 int DPM_TABLE_475__UvdBootLevel__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int ci_enable_uvd_dpm (struct amdgpu_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixDPM_TABLE_475 ; 

__attribute__((used)) static int ci_update_uvd_dpm(struct amdgpu_device *adev, bool gate)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 tmp;
	int ret = 0;

	if (!gate) {
		/* turn the clocks on when decoding */
		if (pi->caps_uvd_dpm ||
		    (adev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.count <= 0))
			pi->smc_state_table.UvdBootLevel = 0;
		else
			pi->smc_state_table.UvdBootLevel =
				adev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.count - 1;

		tmp = RREG32_SMC(ixDPM_TABLE_475);
		tmp &= ~DPM_TABLE_475__UvdBootLevel_MASK;
		tmp |= (pi->smc_state_table.UvdBootLevel << DPM_TABLE_475__UvdBootLevel__SHIFT);
		WREG32_SMC(ixDPM_TABLE_475, tmp);
		ret = ci_enable_uvd_dpm(adev, true);
	} else {
		ret = ci_enable_uvd_dpm(adev, false);
		if (ret)
			return ret;
	}

	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int VceBootLevel; } ;
struct ci_power_info {TYPE_1__ smc_state_table; } ;
struct amdgpu_ps {scalar_t__ evclk; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int DPM_TABLE_475__VceBootLevel_MASK ; 
 int DPM_TABLE_475__VceBootLevel__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int ci_enable_vce_dpm (struct amdgpu_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_get_vce_boot_level (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixDPM_TABLE_475 ; 

__attribute__((used)) static int ci_update_vce_dpm(struct amdgpu_device *adev,
			     struct amdgpu_ps *amdgpu_new_state,
			     struct amdgpu_ps *amdgpu_current_state)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	int ret = 0;
	u32 tmp;

	if (amdgpu_current_state->evclk != amdgpu_new_state->evclk) {
		if (amdgpu_new_state->evclk) {
			pi->smc_state_table.VceBootLevel = ci_get_vce_boot_level(adev);
			tmp = RREG32_SMC(ixDPM_TABLE_475);
			tmp &= ~DPM_TABLE_475__VceBootLevel_MASK;
			tmp |= (pi->smc_state_table.VceBootLevel << DPM_TABLE_475__VceBootLevel__SHIFT);
			WREG32_SMC(ixDPM_TABLE_475, tmp);

			ret = ci_enable_vce_dpm(adev, true);
		} else {
			ret = ci_enable_vce_dpm(adev, false);
			if (ret)
				return ret;
		}
	}
	return ret;
}
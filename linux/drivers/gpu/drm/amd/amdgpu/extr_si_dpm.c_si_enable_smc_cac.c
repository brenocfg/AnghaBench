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
struct si_power_info {scalar_t__ enable_dte; } ;
struct ni_power_info {int support_cac_long_term_average; int cac_enabled; scalar_t__ enable_cac; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_CACLongTermAvgDisable ; 
 int /*<<< orphan*/  PPSMC_CACLongTermAvgEnable ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableCac ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableDTE ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableCac ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableDTE ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_si_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct ni_power_info* ni_get_pi (struct amdgpu_device*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_should_disable_uvd_powertune (struct amdgpu_device*,struct amdgpu_ps*) ; 

__attribute__((used)) static int si_enable_smc_cac(struct amdgpu_device *adev,
			     struct amdgpu_ps *amdgpu_new_state,
			     bool enable)
{
	struct ni_power_info *ni_pi = ni_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);
	PPSMC_Result smc_result;
	int ret = 0;

	if (ni_pi->enable_cac) {
		if (enable) {
			if (!si_should_disable_uvd_powertune(adev, amdgpu_new_state)) {
				if (ni_pi->support_cac_long_term_average) {
					smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_CACLongTermAvgEnable);
					if (smc_result != PPSMC_Result_OK)
						ni_pi->support_cac_long_term_average = false;
				}

				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableCac);
				if (smc_result != PPSMC_Result_OK) {
					ret = -EINVAL;
					ni_pi->cac_enabled = false;
				} else {
					ni_pi->cac_enabled = true;
				}

				if (si_pi->enable_dte) {
					smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_EnableDTE);
					if (smc_result != PPSMC_Result_OK)
						ret = -EINVAL;
				}
			}
		} else if (ni_pi->cac_enabled) {
			if (si_pi->enable_dte)
				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_DisableDTE);

			smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_DisableCac);

			ni_pi->cac_enabled = false;

			if (ni_pi->support_cac_long_term_average)
				smc_result = amdgpu_si_send_msg_to_smc(adev, PPSMC_CACLongTermAvgDisable);
		}
	}
	return ret;
}
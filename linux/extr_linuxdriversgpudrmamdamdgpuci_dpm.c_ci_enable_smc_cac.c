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
struct ci_power_info {int cac_enabled; scalar_t__ caps_cac; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableCac ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableCac ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_enable_smc_cac(struct amdgpu_device *adev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	PPSMC_Result smc_result;
	int ret = 0;

	if (pi->caps_cac) {
		if (enable) {
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_EnableCac);
			if (smc_result != PPSMC_Result_OK) {
				ret = -EINVAL;
				pi->cac_enabled = false;
			} else {
				pi->cac_enabled = true;
			}
		} else if (pi->cac_enabled) {
			amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_DisableCac);
			pi->cac_enabled = false;
		}
	}

	return ret;
}
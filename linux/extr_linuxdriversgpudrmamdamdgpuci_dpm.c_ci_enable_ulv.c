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
struct ci_ulv_parm {scalar_t__ supported; } ;
struct ci_power_info {struct ci_ulv_parm ulv; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableULV ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableULV ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_enable_ulv(struct amdgpu_device *adev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	struct ci_ulv_parm *ulv = &pi->ulv;

	if (ulv->supported) {
		if (enable)
			return (amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_EnableULV) == PPSMC_Result_OK) ?
				0 : -EINVAL;
		else
			return (amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_DisableULV) == PPSMC_Result_OK) ?
				0 : -EINVAL;
	}

	return 0;
}
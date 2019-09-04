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
typedef  int /*<<< orphan*/  u32 ;
struct ci_power_info {int power_containment_features; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int POWERCONTAINMENT_FEATURE_PkgPwrLimit ; 
 int /*<<< orphan*/  PPSMC_MSG_PkgPwrSetLimit ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_set_power_limit(struct amdgpu_device *adev, u32 n)
{
	struct ci_power_info *pi = ci_get_pi(adev);

	if (pi->power_containment_features & POWERCONTAINMENT_FEATURE_PkgPwrLimit) {
		PPSMC_Result smc_result =
			amdgpu_ci_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_PkgPwrSetLimit, n);
		if (smc_result != PPSMC_Result_OK)
			return -EINVAL;
	}

	return 0;
}
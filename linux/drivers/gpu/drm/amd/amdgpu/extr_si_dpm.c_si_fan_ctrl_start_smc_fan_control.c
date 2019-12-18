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
struct si_power_info {int fan_is_controlled_by_smc; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  PPSMC_StartFanControl ; 
 scalar_t__ amdgpu_si_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_fan_ctrl_start_smc_fan_control(struct amdgpu_device *adev)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	PPSMC_Result ret;

	ret = amdgpu_si_send_msg_to_smc(adev, PPSMC_StartFanControl);
	if (ret == PPSMC_Result_OK) {
		si_pi->fan_is_controlled_by_smc = true;
		return 0;
	} else {
		return -EINVAL;
	}
}
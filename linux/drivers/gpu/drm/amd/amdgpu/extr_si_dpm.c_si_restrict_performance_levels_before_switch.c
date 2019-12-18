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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_NoForcedLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_SetEnabledLevels ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_si_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ si_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si_restrict_performance_levels_before_switch(struct amdgpu_device *adev)
{
	if (amdgpu_si_send_msg_to_smc(adev, PPSMC_MSG_NoForcedLevel) != PPSMC_Result_OK)
		return -EINVAL;

	return (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, 1) == PPSMC_Result_OK) ?
		0 : -EINVAL;
}
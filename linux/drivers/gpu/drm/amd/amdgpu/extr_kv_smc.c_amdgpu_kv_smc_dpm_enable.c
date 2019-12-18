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
 int /*<<< orphan*/  PPSMC_MSG_DPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_DPM_Enable ; 
 int amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

int amdgpu_kv_smc_dpm_enable(struct amdgpu_device *adev, bool enable)
{
	if (enable)
		return amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_DPM_Enable);
	else
		return amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_DPM_Disable);
}
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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_GetEnabledMask ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSMC_SYSCON_MSG_ARG_0 ; 

int amdgpu_kv_dpm_get_enable_mask(struct amdgpu_device *adev, u32 *enable_mask)
{
	int ret;

	ret = amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_SCLKDPM_GetEnabledMask);

	if (ret == 0)
		*enable_mask = RREG32_SMC(ixSMC_SYSCON_MSG_ARG_0);

	return ret;
}
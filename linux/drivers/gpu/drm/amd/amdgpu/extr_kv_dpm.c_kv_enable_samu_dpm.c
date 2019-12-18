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
 int /*<<< orphan*/  PPSMC_MSG_SAMUDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_SAMUDPM_Enable ; 
 int amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_enable_samu_dpm(struct amdgpu_device *adev, bool enable)
{
	return amdgpu_kv_notify_message_to_smu(adev, enable ?
					PPSMC_MSG_SAMUDPM_Enable : PPSMC_MSG_SAMUDPM_Disable);
}
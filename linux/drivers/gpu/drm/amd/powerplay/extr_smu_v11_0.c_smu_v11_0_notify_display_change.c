#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smu_context {TYPE_2__* adev; int /*<<< orphan*/  pm_enabled; } ;
struct TYPE_3__ {scalar_t__ vram_type; } ;
struct TYPE_4__ {TYPE_1__ gmc; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VRAM_TYPE_HBM ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_UCLK_BIT ; 
 int /*<<< orphan*/  SMU_MSG_SetUclkFastSwitch ; 
 scalar_t__ smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu_v11_0_notify_display_change(struct smu_context *smu)
{
	int ret = 0;

	if (!smu->pm_enabled)
		return ret;
	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT) &&
	    smu->adev->gmc.vram_type == AMDGPU_VRAM_TYPE_HBM)
		ret = smu_send_smc_msg_with_param(smu, SMU_MSG_SetUclkFastSwitch, 1);

	return ret;
}
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
struct smu10_hwmgr {int vcn_power_gated; int isp_tileA_power_gated; int isp_tileB_power_gated; } ;
struct pp_hwmgr {struct amdgpu_device* adev; scalar_t__ backend; } ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  PPSMC_MSG_SetGfxCGPG ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_init_power_gate_state(struct pp_hwmgr *hwmgr)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);
	struct amdgpu_device *adev = hwmgr->adev;

	smu10_data->vcn_power_gated = true;
	smu10_data->isp_tileA_power_gated = true;
	smu10_data->isp_tileB_power_gated = true;

	if (adev->pg_flags & AMD_PG_SUPPORT_GFX_PG)
		return smum_send_msg_to_smc_with_parameter(hwmgr,
							   PPSMC_MSG_SetGfxCGPG,
							   true);
	else
		return 0;
}
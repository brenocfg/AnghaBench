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
struct smu10_hwmgr {int vcn_power_gated; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCN ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  PPSMC_MSG_PowerDownVcn ; 
 int /*<<< orphan*/  PPSMC_MSG_PowerUpVcn ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smu10_powergate_vcn(struct pp_hwmgr *hwmgr, bool bgate)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (bgate) {
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCN,
						AMD_PG_STATE_GATE);
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_PowerDownVcn, 0);
		smu10_data->vcn_power_gated = true;
	} else {
		smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_PowerUpVcn, 0);
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCN,
						AMD_PG_STATE_UNGATE);
		smu10_data->vcn_power_gated = false;
	}
}
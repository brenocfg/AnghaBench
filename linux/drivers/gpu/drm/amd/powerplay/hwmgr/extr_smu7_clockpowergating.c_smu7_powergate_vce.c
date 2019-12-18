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
struct smu7_hwmgr {int vce_power_gated; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCE ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_clockgating_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_powerdown_vce (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_powerup_vce (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_update_vce_dpm (struct pp_hwmgr*,int) ; 

void smu7_powergate_vce(struct pp_hwmgr *hwmgr, bool bgate)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	data->vce_power_gated = bgate;

	if (bgate) {
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_clockgating_state(hwmgr->adev,
				AMD_IP_BLOCK_TYPE_VCE,
				AMD_CG_STATE_GATE);
		smu7_update_vce_dpm(hwmgr, true);
		smu7_powerdown_vce(hwmgr);
	} else {
		smu7_powerup_vce(hwmgr);
		amdgpu_device_ip_set_clockgating_state(hwmgr->adev,
				AMD_IP_BLOCK_TYPE_VCE,
				AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_UNGATE);
		smu7_update_vce_dpm(hwmgr, false);
	}
}
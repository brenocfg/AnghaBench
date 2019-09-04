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
struct smu8_hwmgr {int uvd_power_gated; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_UVD ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_clockgating_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu8_dpm_powerdown_uvd (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_dpm_powerup_uvd (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu8_dpm_update_uvd_dpm (struct pp_hwmgr*,int) ; 

__attribute__((used)) static void smu8_dpm_powergate_uvd(struct pp_hwmgr *hwmgr, bool bgate)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	data->uvd_power_gated = bgate;

	if (bgate) {
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_clockgating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_CG_STATE_GATE);
		smu8_dpm_update_uvd_dpm(hwmgr, true);
		smu8_dpm_powerdown_uvd(hwmgr);
	} else {
		smu8_dpm_powerup_uvd(hwmgr);
		amdgpu_device_ip_set_clockgating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_PG_STATE_UNGATE);
		smu8_dpm_update_uvd_dpm(hwmgr, false);
	}

}
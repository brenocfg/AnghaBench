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
struct vega20_hwmgr {int vce_power_gated; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCE ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega20_enable_disable_vce_dpm (struct pp_hwmgr*,int) ; 

__attribute__((used)) static void vega20_power_gate_vce(struct pp_hwmgr *hwmgr, bool bgate)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);

	if (data->vce_power_gated == bgate)
		return ;

	data->vce_power_gated = bgate;
	if (bgate) {
		vega20_enable_disable_vce_dpm(hwmgr, !bgate);
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_GATE);
	} else {
		amdgpu_device_ip_set_powergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_UNGATE);
		vega20_enable_disable_vce_dpm(hwmgr, !bgate);
	}

}
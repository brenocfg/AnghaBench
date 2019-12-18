#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {TYPE_5__* hwmgr_func; } ;
struct TYPE_9__ {struct pp_hwmgr* pp_handle; TYPE_1__* pp_funcs; } ;
struct TYPE_8__ {scalar_t__ decode_image_width; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_4__ powerplay; TYPE_3__ uvd; TYPE_2__ pm; int /*<<< orphan*/  smu; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* update_nbdpm_pstate ) (struct pp_hwmgr*,int,int) ;} ;
struct TYPE_6__ {scalar_t__ set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_UVD ; 
 scalar_t__ CHIP_STONEY ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char*,int) ; 
 scalar_t__ WIDTH_4K ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_dpm_set_power_gate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct pp_hwmgr*,int,int) ; 

void amdgpu_dpm_enable_uvd(struct amdgpu_device *adev, bool enable)
{
	int ret = 0;
	if (is_support_sw_smu(adev)) {
	    ret = smu_dpm_set_power_gate(&adev->smu, AMD_IP_BLOCK_TYPE_UVD, enable);
	    if (ret)
		DRM_ERROR("[SW SMU]: dpm enable uvd failed, state = %s, ret = %d. \n",
			  enable ? "true" : "false", ret);
	} else if (adev->powerplay.pp_funcs->set_powergating_by_smu) {
		/* enable/disable UVD */
		mutex_lock(&adev->pm.mutex);
		amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_UVD, !enable);
		mutex_unlock(&adev->pm.mutex);
	}
	/* enable/disable Low Memory PState for UVD (4k videos) */
	if (adev->asic_type == CHIP_STONEY &&
		adev->uvd.decode_image_width >= WIDTH_4K) {
		struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

		if (hwmgr && hwmgr->hwmgr_func &&
		    hwmgr->hwmgr_func->update_nbdpm_pstate)
			hwmgr->hwmgr_func->update_nbdpm_pstate(hwmgr,
							       !enable,
							       true);
	}
}
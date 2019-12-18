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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
struct TYPE_3__ {int (* set_powergating_by_smu ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
#define  AMD_IP_BLOCK_TYPE_ACP 134 
#define  AMD_IP_BLOCK_TYPE_GFX 133 
#define  AMD_IP_BLOCK_TYPE_GMC 132 
#define  AMD_IP_BLOCK_TYPE_SDMA 131 
#define  AMD_IP_BLOCK_TYPE_UVD 130 
#define  AMD_IP_BLOCK_TYPE_VCE 129 
#define  AMD_IP_BLOCK_TYPE_VCN 128 
 int is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_dpm_set_power_gate (int /*<<< orphan*/ *,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,int) ; 

int amdgpu_dpm_set_powergating_by_smu(struct amdgpu_device *adev, uint32_t block_type, bool gate)
{
	int ret = 0;
	bool swsmu = is_support_sw_smu(adev);

	switch (block_type) {
	case AMD_IP_BLOCK_TYPE_GFX:
	case AMD_IP_BLOCK_TYPE_UVD:
	case AMD_IP_BLOCK_TYPE_VCN:
	case AMD_IP_BLOCK_TYPE_VCE:
	case AMD_IP_BLOCK_TYPE_SDMA:
		if (swsmu)
			ret = smu_dpm_set_power_gate(&adev->smu, block_type, gate);
		else
			ret = ((adev)->powerplay.pp_funcs->set_powergating_by_smu(
				(adev)->powerplay.pp_handle, block_type, gate));
		break;
	case AMD_IP_BLOCK_TYPE_GMC:
	case AMD_IP_BLOCK_TYPE_ACP:
		ret = ((adev)->powerplay.pp_funcs->set_powergating_by_smu(
				(adev)->powerplay.pp_handle, block_type, gate));
		break;
	default:
		break;
	}

	return ret;
}
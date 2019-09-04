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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int cg_flags; TYPE_2__ powerplay; } ;
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;
struct TYPE_3__ {scalar_t__ set_clockgating_by_smu; } ;

/* Variables and functions */
 int AMD_CG_STATE_UNGATE ; 
 int AMD_CG_SUPPORT_BIF_LS ; 
 int AMD_CG_SUPPORT_BIF_MGCG ; 
 int AMD_CG_SUPPORT_DRM_LS ; 
 int AMD_CG_SUPPORT_HDP_LS ; 
 int AMD_CG_SUPPORT_HDP_MGCG ; 
 int AMD_CG_SUPPORT_MC_LS ; 
 int AMD_CG_SUPPORT_MC_MGCG ; 
 int AMD_CG_SUPPORT_ROM_MGCG ; 
 int AMD_CG_SUPPORT_SDMA_LS ; 
 int AMD_CG_SUPPORT_SDMA_MGCG ; 
 int /*<<< orphan*/  PP_BLOCK_SYS_BIF ; 
 int /*<<< orphan*/  PP_BLOCK_SYS_DRM ; 
 int /*<<< orphan*/  PP_BLOCK_SYS_HDP ; 
 int /*<<< orphan*/  PP_BLOCK_SYS_MC ; 
 int /*<<< orphan*/  PP_BLOCK_SYS_ROM ; 
 int /*<<< orphan*/  PP_BLOCK_SYS_SDMA ; 
 int /*<<< orphan*/  PP_CG_MSG_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_GROUP_SYS ; 
 int /*<<< orphan*/  PP_STATE_CG ; 
 int /*<<< orphan*/  PP_STATE_LS ; 
 int /*<<< orphan*/  PP_STATE_SUPPORT_CG ; 
 int /*<<< orphan*/  PP_STATE_SUPPORT_LS ; 
 int /*<<< orphan*/  amdgpu_dpm_set_clockgating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vi_common_set_clockgating_state_by_smu(void *handle,
					   enum amd_clockgating_state state)
{
	uint32_t msg_id, pp_state = 0;
	uint32_t pp_support_state = 0;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->cg_flags & (AMD_CG_SUPPORT_MC_LS | AMD_CG_SUPPORT_MC_MGCG)) {
		if (adev->cg_flags & AMD_CG_SUPPORT_MC_LS) {
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		}
		if (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG) {
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_MC,
			       pp_support_state,
			       pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_flags & (AMD_CG_SUPPORT_SDMA_LS | AMD_CG_SUPPORT_SDMA_MGCG)) {
		if (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS) {
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		}
		if (adev->cg_flags & AMD_CG_SUPPORT_SDMA_MGCG) {
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_SDMA,
			       pp_support_state,
			       pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_flags & (AMD_CG_SUPPORT_HDP_LS | AMD_CG_SUPPORT_HDP_MGCG)) {
		if (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS) {
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		}
		if (adev->cg_flags & AMD_CG_SUPPORT_HDP_MGCG) {
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_HDP,
			       pp_support_state,
			       pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}


	if (adev->cg_flags & AMD_CG_SUPPORT_BIF_LS) {
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		else
			pp_state = PP_STATE_LS;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_BIF,
			       PP_STATE_SUPPORT_LS,
			        pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}
	if (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG) {
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		else
			pp_state = PP_STATE_CG;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_BIF,
			       PP_STATE_SUPPORT_CG,
			       pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_flags & AMD_CG_SUPPORT_DRM_LS) {

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		else
			pp_state = PP_STATE_LS;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_DRM,
			       PP_STATE_SUPPORT_LS,
			       pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_flags & AMD_CG_SUPPORT_ROM_MGCG) {

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		else
			pp_state = PP_STATE_CG;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_ROM,
			       PP_STATE_SUPPORT_CG,
			       pp_state);
		if (adev->powerplay.pp_funcs->set_clockgating_by_smu)
			amdgpu_dpm_set_clockgating_by_smu(adev, msg_id);
	}
	return 0;
}
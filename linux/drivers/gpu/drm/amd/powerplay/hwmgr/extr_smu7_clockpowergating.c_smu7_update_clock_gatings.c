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
typedef  int uint32_t ;
struct pp_hwmgr {int feature_mask; } ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 int CG_CPF_MGCG_MASK ; 
 int CG_GFX_3DCG_MASK ; 
 int CG_GFX_3DLS_MASK ; 
 int CG_GFX_CGCG_MASK ; 
 int CG_GFX_CGLS_MASK ; 
 int CG_GFX_CP_LS_MASK ; 
 int CG_GFX_OTHERS_MGCG_MASK ; 
 int CG_GFX_RLC_LS_MASK ; 
 int CG_RLC_MGCG_MASK ; 
 int CG_SYS_BIF_MGCG_MASK ; 
 int CG_SYS_BIF_MGLS_MASK ; 
 int CG_SYS_DRM_MGCG_MASK ; 
 int CG_SYS_DRM_MGLS_MASK ; 
 int CG_SYS_HDP_MGCG_MASK ; 
 int CG_SYS_HDP_MGLS_MASK ; 
 int CG_SYS_MC_MGCG_MASK ; 
 int CG_SYS_MC_MGLS_MASK ; 
 int CG_SYS_ROM_MASK ; 
 int CG_SYS_SDMA_MGCG_MASK ; 
 int CG_SYS_SDMA_MGLS_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableClockGatingFeature ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableClockGatingFeature ; 
#define  PP_BLOCK_GFX_3D 140 
#define  PP_BLOCK_GFX_CG 139 
#define  PP_BLOCK_GFX_CP 138 
#define  PP_BLOCK_GFX_MG 137 
#define  PP_BLOCK_GFX_RLC 136 
 int const PP_BLOCK_MASK ; 
 int const PP_BLOCK_SHIFT ; 
#define  PP_BLOCK_SYS_BIF 135 
#define  PP_BLOCK_SYS_DRM 134 
#define  PP_BLOCK_SYS_HDP 133 
#define  PP_BLOCK_SYS_MC 132 
#define  PP_BLOCK_SYS_ROM 131 
#define  PP_BLOCK_SYS_SDMA 130 
 int PP_ENABLE_GFX_CG_THRU_SMU ; 
#define  PP_GROUP_GFX 129 
 int const PP_GROUP_MASK ; 
 int const PP_GROUP_SHIFT ; 
#define  PP_GROUP_SYS 128 
 int const PP_STATE_CG ; 
 int const PP_STATE_LS ; 
 int const PP_STATE_MASK ; 
 int const PP_STATE_SUPPORT_CG ; 
 int const PP_STATE_SUPPORT_LS ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

int smu7_update_clock_gatings(struct pp_hwmgr *hwmgr,
					const uint32_t *msg_id)
{
	PPSMC_Msg msg;
	uint32_t value;

	if (!(hwmgr->feature_mask & PP_ENABLE_GFX_CG_THRU_SMU))
		return 0;

	switch ((*msg_id & PP_GROUP_MASK) >> PP_GROUP_SHIFT) {
	case PP_GROUP_GFX:
		switch ((*msg_id & PP_BLOCK_MASK) >> PP_BLOCK_SHIFT) {
		case PP_BLOCK_GFX_CG:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_CGCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS
					? PPSMC_MSG_EnableClockGatingFeature
					: PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_CGLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_GFX_3D:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_3DCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}

			if  (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_3DLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_GFX_RLC:
			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_RLC_LS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_GFX_CP:
			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_CP_LS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_GFX_MG:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = (CG_CPF_MGCG_MASK | CG_RLC_MGCG_MASK |
						CG_GFX_OTHERS_MGCG_MASK);

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		default:
			return -EINVAL;
		}
		break;

	case PP_GROUP_SYS:
		switch ((*msg_id & PP_BLOCK_MASK) >> PP_BLOCK_SHIFT) {
		case PP_BLOCK_SYS_BIF:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_CG ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_BIF_MGCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			if  (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_BIF_MGLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_SYS_MC:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_MC_MGCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}

			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_MC_MGLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_SYS_DRM:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_CG ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_DRM_MGCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_DRM_MGLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_SYS_HDP:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_HDP_MGCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}

			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_HDP_MGLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_SYS_SDMA:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_SDMA_MGCG_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}

			if (PP_STATE_SUPPORT_LS & *msg_id) {
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_SDMA_MGLS_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		case PP_BLOCK_SYS_ROM:
			if (PP_STATE_SUPPORT_CG & *msg_id) {
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_ROM_MASK;

				if (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value))
					return -EINVAL;
			}
			break;

		default:
			return -EINVAL;

		}
		break;

	default:
		return -EINVAL;

	}

	return 0;
}
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
struct amdgpu_firmware_info {int ucode_id; } ;
typedef  enum psp_gfx_fw_type { ____Placeholder_psp_gfx_fw_type } psp_gfx_fw_type ;

/* Variables and functions */
#define  AMDGPU_UCODE_ID_CP_CE 145 
#define  AMDGPU_UCODE_ID_CP_ME 144 
#define  AMDGPU_UCODE_ID_CP_MEC1 143 
#define  AMDGPU_UCODE_ID_CP_MEC1_JT 142 
#define  AMDGPU_UCODE_ID_CP_MEC2 141 
#define  AMDGPU_UCODE_ID_CP_MEC2_JT 140 
#define  AMDGPU_UCODE_ID_CP_PFP 139 
#define  AMDGPU_UCODE_ID_MAXIMUM 138 
#define  AMDGPU_UCODE_ID_RLC_G 137 
#define  AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL 136 
#define  AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM 135 
#define  AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM 134 
#define  AMDGPU_UCODE_ID_SDMA0 133 
#define  AMDGPU_UCODE_ID_SDMA1 132 
#define  AMDGPU_UCODE_ID_SMC 131 
#define  AMDGPU_UCODE_ID_UVD 130 
#define  AMDGPU_UCODE_ID_VCE 129 
#define  AMDGPU_UCODE_ID_VCN 128 
 int EINVAL ; 
 int GFX_FW_TYPE_CP_CE ; 
 int GFX_FW_TYPE_CP_ME ; 
 int GFX_FW_TYPE_CP_MEC ; 
 int GFX_FW_TYPE_CP_MEC_ME1 ; 
 int GFX_FW_TYPE_CP_MEC_ME2 ; 
 int GFX_FW_TYPE_CP_PFP ; 
 int GFX_FW_TYPE_RLC_G ; 
 int GFX_FW_TYPE_RLC_RESTORE_LIST_CNTL ; 
 int GFX_FW_TYPE_RLC_RESTORE_LIST_GPM_MEM ; 
 int GFX_FW_TYPE_RLC_RESTORE_LIST_SRM_MEM ; 
 int GFX_FW_TYPE_SDMA0 ; 
 int GFX_FW_TYPE_SDMA1 ; 
 int GFX_FW_TYPE_SMU ; 
 int GFX_FW_TYPE_UVD ; 
 int GFX_FW_TYPE_VCE ; 
 int GFX_FW_TYPE_VCN ; 

__attribute__((used)) static int
psp_v10_0_get_fw_type(struct amdgpu_firmware_info *ucode, enum psp_gfx_fw_type *type)
{
	switch(ucode->ucode_id) {
	case AMDGPU_UCODE_ID_SDMA0:
		*type = GFX_FW_TYPE_SDMA0;
		break;
	case AMDGPU_UCODE_ID_SDMA1:
		*type = GFX_FW_TYPE_SDMA1;
		break;
	case AMDGPU_UCODE_ID_CP_CE:
		*type = GFX_FW_TYPE_CP_CE;
		break;
	case AMDGPU_UCODE_ID_CP_PFP:
		*type = GFX_FW_TYPE_CP_PFP;
		break;
	case AMDGPU_UCODE_ID_CP_ME:
		*type = GFX_FW_TYPE_CP_ME;
		break;
	case AMDGPU_UCODE_ID_CP_MEC1:
		*type = GFX_FW_TYPE_CP_MEC;
		break;
	case AMDGPU_UCODE_ID_CP_MEC1_JT:
		*type = GFX_FW_TYPE_CP_MEC_ME1;
		break;
	case AMDGPU_UCODE_ID_CP_MEC2:
		*type = GFX_FW_TYPE_CP_MEC;
		break;
	case AMDGPU_UCODE_ID_CP_MEC2_JT:
		*type = GFX_FW_TYPE_CP_MEC_ME2;
		break;
	case AMDGPU_UCODE_ID_RLC_G:
		*type = GFX_FW_TYPE_RLC_G;
		break;
	case AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL:
		*type = GFX_FW_TYPE_RLC_RESTORE_LIST_CNTL;
		break;
	case AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM:
		*type = GFX_FW_TYPE_RLC_RESTORE_LIST_GPM_MEM;
		break;
	case AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM:
		*type = GFX_FW_TYPE_RLC_RESTORE_LIST_SRM_MEM;
		break;
	case AMDGPU_UCODE_ID_SMC:
		*type = GFX_FW_TYPE_SMU;
		break;
	case AMDGPU_UCODE_ID_UVD:
		*type = GFX_FW_TYPE_UVD;
		break;
	case AMDGPU_UCODE_ID_VCE:
		*type = GFX_FW_TYPE_VCE;
		break;
	case AMDGPU_UCODE_ID_VCN:
		*type = GFX_FW_TYPE_VCN;
		break;
	case AMDGPU_UCODE_ID_MAXIMUM:
	default:
		return -EINVAL;
	}

	return 0;
}
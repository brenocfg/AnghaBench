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
#define  AMDGPU_UCODE_ID_CP_CE 141 
#define  AMDGPU_UCODE_ID_CP_ME 140 
#define  AMDGPU_UCODE_ID_CP_MEC1 139 
#define  AMDGPU_UCODE_ID_CP_MEC1_JT 138 
#define  AMDGPU_UCODE_ID_CP_MEC2 137 
#define  AMDGPU_UCODE_ID_CP_MEC2_JT 136 
#define  AMDGPU_UCODE_ID_CP_PFP 135 
#define  AMDGPU_UCODE_ID_MAXIMUM 134 
#define  AMDGPU_UCODE_ID_RLC_G 133 
#define  AMDGPU_UCODE_ID_SDMA0 132 
#define  AMDGPU_UCODE_ID_SDMA1 131 
#define  AMDGPU_UCODE_ID_SMC 130 
#define  AMDGPU_UCODE_ID_UVD 129 
#define  AMDGPU_UCODE_ID_VCE 128 
 int EINVAL ; 
 int GFX_FW_TYPE_CP_CE ; 
 int GFX_FW_TYPE_CP_ME ; 
 int GFX_FW_TYPE_CP_MEC ; 
 int GFX_FW_TYPE_CP_MEC_ME1 ; 
 int GFX_FW_TYPE_CP_MEC_ME2 ; 
 int GFX_FW_TYPE_CP_PFP ; 
 int GFX_FW_TYPE_RLC_G ; 
 int GFX_FW_TYPE_SDMA0 ; 
 int GFX_FW_TYPE_SDMA1 ; 
 int GFX_FW_TYPE_SMU ; 
 int GFX_FW_TYPE_UVD ; 
 int GFX_FW_TYPE_VCE ; 

__attribute__((used)) static int
psp_v3_1_get_fw_type(struct amdgpu_firmware_info *ucode, enum psp_gfx_fw_type *type)
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
	case AMDGPU_UCODE_ID_SMC:
		*type = GFX_FW_TYPE_SMU;
		break;
	case AMDGPU_UCODE_ID_UVD:
		*type = GFX_FW_TYPE_UVD;
		break;
	case AMDGPU_UCODE_ID_VCE:
		*type = GFX_FW_TYPE_VCE;
		break;
	case AMDGPU_UCODE_ID_MAXIMUM:
	default:
		return -EINVAL;
	}

	return 0;
}
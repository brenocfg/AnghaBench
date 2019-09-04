#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct drm_amdgpu_query_fw {int fw_type; int index; } ;
struct drm_amdgpu_info_firmware {int /*<<< orphan*/  feature; int /*<<< orphan*/  ver; } ;
struct TYPE_18__ {int /*<<< orphan*/  asd_feature_version; int /*<<< orphan*/  asd_fw_version; int /*<<< orphan*/  sos_feature_version; int /*<<< orphan*/  sos_fw_version; } ;
struct TYPE_17__ {int num_instances; TYPE_7__* instance; } ;
struct TYPE_15__ {int /*<<< orphan*/  fw_version; } ;
struct TYPE_14__ {int /*<<< orphan*/  mec2_feature_version; int /*<<< orphan*/  mec2_fw_version; int /*<<< orphan*/  mec_feature_version; int /*<<< orphan*/  mec_fw_version; int /*<<< orphan*/  rlc_srls_feature_version; int /*<<< orphan*/  rlc_srls_fw_version; int /*<<< orphan*/  rlc_srlg_feature_version; int /*<<< orphan*/  rlc_srlg_fw_version; int /*<<< orphan*/  rlc_srlc_feature_version; int /*<<< orphan*/  rlc_srlc_fw_version; int /*<<< orphan*/  rlc_feature_version; int /*<<< orphan*/  rlc_fw_version; int /*<<< orphan*/  ce_feature_version; int /*<<< orphan*/  ce_fw_version; int /*<<< orphan*/  pfp_feature_version; int /*<<< orphan*/  pfp_fw_version; int /*<<< orphan*/  me_feature_version; int /*<<< orphan*/  me_fw_version; } ;
struct TYPE_13__ {int /*<<< orphan*/  fw_version; } ;
struct TYPE_12__ {int /*<<< orphan*/  fw_version; } ;
struct TYPE_11__ {int /*<<< orphan*/  fw_version; } ;
struct TYPE_10__ {int /*<<< orphan*/  fb_version; int /*<<< orphan*/  fw_version; } ;
struct amdgpu_device {TYPE_9__ psp; TYPE_8__ sdma; TYPE_6__ pm; TYPE_5__ gfx; TYPE_4__ gmc; TYPE_3__ vcn; TYPE_2__ uvd; TYPE_1__ vce; } ;
struct TYPE_16__ {int /*<<< orphan*/  feature_version; int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
#define  AMDGPU_INFO_FW_ASD 143 
#define  AMDGPU_INFO_FW_GFX_CE 142 
#define  AMDGPU_INFO_FW_GFX_ME 141 
#define  AMDGPU_INFO_FW_GFX_MEC 140 
#define  AMDGPU_INFO_FW_GFX_PFP 139 
#define  AMDGPU_INFO_FW_GFX_RLC 138 
#define  AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_CNTL 137 
#define  AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_GPM_MEM 136 
#define  AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_SRM_MEM 135 
#define  AMDGPU_INFO_FW_GMC 134 
#define  AMDGPU_INFO_FW_SDMA 133 
#define  AMDGPU_INFO_FW_SMC 132 
#define  AMDGPU_INFO_FW_SOS 131 
#define  AMDGPU_INFO_FW_UVD 130 
#define  AMDGPU_INFO_FW_VCE 129 
#define  AMDGPU_INFO_FW_VCN 128 
 int EINVAL ; 

__attribute__((used)) static int amdgpu_firmware_info(struct drm_amdgpu_info_firmware *fw_info,
				struct drm_amdgpu_query_fw *query_fw,
				struct amdgpu_device *adev)
{
	switch (query_fw->fw_type) {
	case AMDGPU_INFO_FW_VCE:
		fw_info->ver = adev->vce.fw_version;
		fw_info->feature = adev->vce.fb_version;
		break;
	case AMDGPU_INFO_FW_UVD:
		fw_info->ver = adev->uvd.fw_version;
		fw_info->feature = 0;
		break;
	case AMDGPU_INFO_FW_VCN:
		fw_info->ver = adev->vcn.fw_version;
		fw_info->feature = 0;
		break;
	case AMDGPU_INFO_FW_GMC:
		fw_info->ver = adev->gmc.fw_version;
		fw_info->feature = 0;
		break;
	case AMDGPU_INFO_FW_GFX_ME:
		fw_info->ver = adev->gfx.me_fw_version;
		fw_info->feature = adev->gfx.me_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_PFP:
		fw_info->ver = adev->gfx.pfp_fw_version;
		fw_info->feature = adev->gfx.pfp_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_CE:
		fw_info->ver = adev->gfx.ce_fw_version;
		fw_info->feature = adev->gfx.ce_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_RLC:
		fw_info->ver = adev->gfx.rlc_fw_version;
		fw_info->feature = adev->gfx.rlc_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_CNTL:
		fw_info->ver = adev->gfx.rlc_srlc_fw_version;
		fw_info->feature = adev->gfx.rlc_srlc_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_GPM_MEM:
		fw_info->ver = adev->gfx.rlc_srlg_fw_version;
		fw_info->feature = adev->gfx.rlc_srlg_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_SRM_MEM:
		fw_info->ver = adev->gfx.rlc_srls_fw_version;
		fw_info->feature = adev->gfx.rlc_srls_feature_version;
		break;
	case AMDGPU_INFO_FW_GFX_MEC:
		if (query_fw->index == 0) {
			fw_info->ver = adev->gfx.mec_fw_version;
			fw_info->feature = adev->gfx.mec_feature_version;
		} else if (query_fw->index == 1) {
			fw_info->ver = adev->gfx.mec2_fw_version;
			fw_info->feature = adev->gfx.mec2_feature_version;
		} else
			return -EINVAL;
		break;
	case AMDGPU_INFO_FW_SMC:
		fw_info->ver = adev->pm.fw_version;
		fw_info->feature = 0;
		break;
	case AMDGPU_INFO_FW_SDMA:
		if (query_fw->index >= adev->sdma.num_instances)
			return -EINVAL;
		fw_info->ver = adev->sdma.instance[query_fw->index].fw_version;
		fw_info->feature = adev->sdma.instance[query_fw->index].feature_version;
		break;
	case AMDGPU_INFO_FW_SOS:
		fw_info->ver = adev->psp.sos_fw_version;
		fw_info->feature = adev->psp.sos_feature_version;
		break;
	case AMDGPU_INFO_FW_ASD:
		fw_info->ver = adev->psp.asd_fw_version;
		fw_info->feature = adev->psp.asd_feature_version;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
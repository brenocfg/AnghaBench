#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct cgs_device {int dummy; } ;
typedef  enum cgs_ucode_id { ____Placeholder_cgs_ucode_id } cgs_ucode_id ;
struct TYPE_7__ {int /*<<< orphan*/  rlc_fw_version; int /*<<< orphan*/  mec_fw_version; int /*<<< orphan*/  me_fw_version; int /*<<< orphan*/  pfp_fw_version; int /*<<< orphan*/  ce_fw_version; } ;
struct TYPE_6__ {TYPE_1__* instance; } ;
struct TYPE_8__ {TYPE_3__ gfx; TYPE_2__ sdma; } ;
struct TYPE_5__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_FUNC_ADEV ; 
#define  CGS_UCODE_ID_CP_CE 137 
#define  CGS_UCODE_ID_CP_ME 136 
#define  CGS_UCODE_ID_CP_MEC 135 
#define  CGS_UCODE_ID_CP_MEC_JT1 134 
#define  CGS_UCODE_ID_CP_MEC_JT2 133 
#define  CGS_UCODE_ID_CP_PFP 132 
#define  CGS_UCODE_ID_RLC_G 131 
#define  CGS_UCODE_ID_SDMA0 130 
#define  CGS_UCODE_ID_SDMA1 129 
#define  CGS_UCODE_ID_STORAGE 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 TYPE_4__* adev ; 

__attribute__((used)) static uint16_t amdgpu_get_firmware_version(struct cgs_device *cgs_device,
					enum cgs_ucode_id type)
{
	CGS_FUNC_ADEV;
	uint16_t fw_version = 0;

	switch (type) {
		case CGS_UCODE_ID_SDMA0:
			fw_version = adev->sdma.instance[0].fw_version;
			break;
		case CGS_UCODE_ID_SDMA1:
			fw_version = adev->sdma.instance[1].fw_version;
			break;
		case CGS_UCODE_ID_CP_CE:
			fw_version = adev->gfx.ce_fw_version;
			break;
		case CGS_UCODE_ID_CP_PFP:
			fw_version = adev->gfx.pfp_fw_version;
			break;
		case CGS_UCODE_ID_CP_ME:
			fw_version = adev->gfx.me_fw_version;
			break;
		case CGS_UCODE_ID_CP_MEC:
			fw_version = adev->gfx.mec_fw_version;
			break;
		case CGS_UCODE_ID_CP_MEC_JT1:
			fw_version = adev->gfx.mec_fw_version;
			break;
		case CGS_UCODE_ID_CP_MEC_JT2:
			fw_version = adev->gfx.mec_fw_version;
			break;
		case CGS_UCODE_ID_RLC_G:
			fw_version = adev->gfx.rlc_fw_version;
			break;
		case CGS_UCODE_ID_STORAGE:
			break;
		default:
			DRM_ERROR("firmware type %d do not have version\n", type);
			break;
	}
	return fw_version;
}
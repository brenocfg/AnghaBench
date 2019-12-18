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
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  checksum_key; struct amd_sriov_msg_pf2vf_info_header* p_vf2pf; struct amd_sriov_msg_pf2vf_info_header* p_pf2vf; } ;
struct TYPE_8__ {int gim_feature; TYPE_2__ fw_reserve; } ;
struct TYPE_6__ {int /*<<< orphan*/ * va; } ;
struct amdgpu_device {TYPE_3__ virt; TYPE_1__ fw_vram_usage; } ;
struct amd_sriov_msg_pf2vf_info_header {int dummy; } ;
typedef  int /*<<< orphan*/  amdgim_vf2pf_info ;
struct TYPE_10__ {char* version; } ;
struct TYPE_9__ {int size; int version; } ;

/* Variables and functions */
 int AMDGIM_DATAEXCHANGE_OFFSET ; 
 int /*<<< orphan*/  AMDGPU_FW_VRAM_PF2VF_READ (struct amdgpu_device*,int,int*) ; 
 int /*<<< orphan*/  AMDGPU_FW_VRAM_VF2PF_READ (struct amdgpu_device*,int /*<<< orphan*/ ,char**) ; 
 int AMDGPU_FW_VRAM_VF2PF_VER ; 
 int /*<<< orphan*/  AMDGPU_FW_VRAM_VF2PF_WRITE (struct amdgpu_device*,int,int) ; 
 TYPE_5__* THIS_MODULE ; 
 int amdgpu_virt_fw_reserve_get_checksum (struct amd_sriov_msg_pf2vf_info_header*,int,int /*<<< orphan*/ ,int) ; 
 int driver_cert ; 
 int /*<<< orphan*/  driver_version ; 
 int feature_flags ; 
 TYPE_4__ header ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void amdgpu_virt_init_data_exchange(struct amdgpu_device *adev)
{
	uint32_t pf2vf_size = 0;
	uint32_t checksum = 0;
	uint32_t checkval;
	char *str;

	adev->virt.fw_reserve.p_pf2vf = NULL;
	adev->virt.fw_reserve.p_vf2pf = NULL;

	if (adev->fw_vram_usage.va != NULL) {
		adev->virt.fw_reserve.p_pf2vf =
			(struct amd_sriov_msg_pf2vf_info_header *)(
			adev->fw_vram_usage.va + AMDGIM_DATAEXCHANGE_OFFSET);
		AMDGPU_FW_VRAM_PF2VF_READ(adev, header.size, &pf2vf_size);
		AMDGPU_FW_VRAM_PF2VF_READ(adev, checksum, &checksum);
		AMDGPU_FW_VRAM_PF2VF_READ(adev, feature_flags, &adev->virt.gim_feature);

		/* pf2vf message must be in 4K */
		if (pf2vf_size > 0 && pf2vf_size < 4096) {
			checkval = amdgpu_virt_fw_reserve_get_checksum(
				adev->virt.fw_reserve.p_pf2vf, pf2vf_size,
				adev->virt.fw_reserve.checksum_key, checksum);
			if (checkval == checksum) {
				adev->virt.fw_reserve.p_vf2pf =
					((void *)adev->virt.fw_reserve.p_pf2vf +
					pf2vf_size);
				memset((void *)adev->virt.fw_reserve.p_vf2pf, 0,
					sizeof(amdgim_vf2pf_info));
				AMDGPU_FW_VRAM_VF2PF_WRITE(adev, header.version,
					AMDGPU_FW_VRAM_VF2PF_VER);
				AMDGPU_FW_VRAM_VF2PF_WRITE(adev, header.size,
					sizeof(amdgim_vf2pf_info));
				AMDGPU_FW_VRAM_VF2PF_READ(adev, driver_version,
					&str);
#ifdef MODULE
				if (THIS_MODULE->version != NULL)
					strcpy(str, THIS_MODULE->version);
				else
#endif
					strcpy(str, "N/A");
				AMDGPU_FW_VRAM_VF2PF_WRITE(adev, driver_cert,
					0);
				AMDGPU_FW_VRAM_VF2PF_WRITE(adev, checksum,
					amdgpu_virt_fw_reserve_get_checksum(
					adev->virt.fw_reserve.p_vf2pf,
					pf2vf_size,
					adev->virt.fw_reserve.checksum_key, 0));
			}
		}
	}
}
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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  jt_offset; int /*<<< orphan*/  jt_size; } ;
struct dmcu_firmware_header_v1_0 {int /*<<< orphan*/  intv_offset_bytes; int /*<<< orphan*/  intv_size_bytes; } ;
struct common_firmware_header {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; } ;
struct amdgpu_firmware_info {scalar_t__ ucode_id; int ucode_size; void* kaddr; TYPE_2__* fw; int /*<<< orphan*/  mc_addr; } ;
struct TYPE_7__ {int save_restore_list_cntl_size_bytes; void* save_restore_list_cntl; int save_restore_list_gpm_size_bytes; void* save_restore_list_gpm; int save_restore_list_srm_size_bytes; void* save_restore_list_srm; } ;
struct TYPE_8__ {TYPE_3__ rlc; } ;
struct TYPE_5__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_4__ gfx; TYPE_1__ firmware; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 scalar_t__ AMDGPU_UCODE_ID_CP_MEC1 ; 
 scalar_t__ AMDGPU_UCODE_ID_CP_MEC1_JT ; 
 scalar_t__ AMDGPU_UCODE_ID_CP_MEC2 ; 
 scalar_t__ AMDGPU_UCODE_ID_CP_MEC2_JT ; 
 scalar_t__ AMDGPU_UCODE_ID_DMCU_ERAM ; 
 scalar_t__ AMDGPU_UCODE_ID_DMCU_INTV ; 
 scalar_t__ AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL ; 
 scalar_t__ AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM ; 
 scalar_t__ AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM ; 
 scalar_t__ AMDGPU_UCODE_ID_STORAGE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static int amdgpu_ucode_init_single_fw(struct amdgpu_device *adev,
				       struct amdgpu_firmware_info *ucode,
				       uint64_t mc_addr, void *kptr)
{
	const struct common_firmware_header *header = NULL;
	const struct gfx_firmware_header_v1_0 *cp_hdr = NULL;
	const struct dmcu_firmware_header_v1_0 *dmcu_hdr = NULL;

	if (NULL == ucode->fw)
		return 0;

	ucode->mc_addr = mc_addr;
	ucode->kaddr = kptr;

	if (ucode->ucode_id == AMDGPU_UCODE_ID_STORAGE)
		return 0;

	header = (const struct common_firmware_header *)ucode->fw->data;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)ucode->fw->data;
	dmcu_hdr = (const struct dmcu_firmware_header_v1_0 *)ucode->fw->data;

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP ||
	    (ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC1 &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC2 &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC1_JT &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_CP_MEC2_JT &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM &&
	     ucode->ucode_id != AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM &&
		 ucode->ucode_id != AMDGPU_UCODE_ID_DMCU_ERAM &&
		 ucode->ucode_id != AMDGPU_UCODE_ID_DMCU_INTV)) {
		ucode->ucode_size = le32_to_cpu(header->ucode_size_bytes);

		memcpy(ucode->kaddr, (void *)((uint8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC1 ||
		   ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2) {
		ucode->ucode_size = le32_to_cpu(header->ucode_size_bytes) -
			le32_to_cpu(cp_hdr->jt_size) * 4;

		memcpy(ucode->kaddr, (void *)((uint8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC1_JT ||
		   ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2_JT) {
		ucode->ucode_size = le32_to_cpu(cp_hdr->jt_size) * 4;

		memcpy(ucode->kaddr, (void *)((uint8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes) +
					      le32_to_cpu(cp_hdr->jt_offset) * 4),
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_DMCU_ERAM) {
		ucode->ucode_size = le32_to_cpu(header->ucode_size_bytes) -
				le32_to_cpu(dmcu_hdr->intv_size_bytes);

		memcpy(ucode->kaddr, (void *)((uint8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes)),
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_DMCU_INTV) {
		ucode->ucode_size = le32_to_cpu(dmcu_hdr->intv_size_bytes);

		memcpy(ucode->kaddr, (void *)((uint8_t *)ucode->fw->data +
					      le32_to_cpu(header->ucode_array_offset_bytes) +
					      le32_to_cpu(dmcu_hdr->intv_offset_bytes)),
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL) {
		ucode->ucode_size = adev->gfx.rlc.save_restore_list_cntl_size_bytes;
		memcpy(ucode->kaddr, adev->gfx.rlc.save_restore_list_cntl,
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM) {
		ucode->ucode_size = adev->gfx.rlc.save_restore_list_gpm_size_bytes;
		memcpy(ucode->kaddr, adev->gfx.rlc.save_restore_list_gpm,
		       ucode->ucode_size);
	} else if (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM) {
		ucode->ucode_size = adev->gfx.rlc.save_restore_list_srm_size_bytes;
		memcpy(ucode->kaddr, adev->gfx.rlc.save_restore_list_srm,
		       ucode->ucode_size);
	}

	return 0;
}
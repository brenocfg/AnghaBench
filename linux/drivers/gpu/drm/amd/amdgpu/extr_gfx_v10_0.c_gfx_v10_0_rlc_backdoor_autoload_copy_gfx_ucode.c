#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct rlc_firmware_header_v2_0 {TYPE_5__ header; } ;
struct TYPE_16__ {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {int jt_size; TYPE_8__ header; } ;
struct TYPE_15__ {TYPE_6__* mec_fw; TYPE_4__* rlc_fw; TYPE_3__* me_fw; TYPE_2__* ce_fw; TYPE_1__* pfp_fw; } ;
struct amdgpu_device {TYPE_7__ gfx; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_ID_CP_CE ; 
 int /*<<< orphan*/  FIRMWARE_ID_CP_ME ; 
 int /*<<< orphan*/  FIRMWARE_ID_CP_MEC ; 
 int /*<<< orphan*/  FIRMWARE_ID_CP_PFP ; 
 int /*<<< orphan*/  FIRMWARE_ID_RLC_G_UCODE ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_backdoor_autoload_copy_ucode (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_v10_0_rlc_backdoor_autoload_copy_gfx_ucode(struct amdgpu_device *adev)
{
	const __le32 *fw_data;
	uint32_t fw_size;
	const struct gfx_firmware_header_v1_0 *cp_hdr;
	const struct rlc_firmware_header_v2_0 *rlc_hdr;

	/* pfp ucode */
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)
		adev->gfx.pfp_fw->data;
	fw_data = (const __le32 *)(adev->gfx.pfp_fw->data +
		le32_to_cpu(cp_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(cp_hdr->header.ucode_size_bytes);
	gfx_v10_0_rlc_backdoor_autoload_copy_ucode(adev,
						   FIRMWARE_ID_CP_PFP,
						   fw_data, fw_size);

	/* ce ucode */
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)
		adev->gfx.ce_fw->data;
	fw_data = (const __le32 *)(adev->gfx.ce_fw->data +
		le32_to_cpu(cp_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(cp_hdr->header.ucode_size_bytes);
	gfx_v10_0_rlc_backdoor_autoload_copy_ucode(adev,
						   FIRMWARE_ID_CP_CE,
						   fw_data, fw_size);

	/* me ucode */
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)
		adev->gfx.me_fw->data;
	fw_data = (const __le32 *)(adev->gfx.me_fw->data +
		le32_to_cpu(cp_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(cp_hdr->header.ucode_size_bytes);
	gfx_v10_0_rlc_backdoor_autoload_copy_ucode(adev,
						   FIRMWARE_ID_CP_ME,
						   fw_data, fw_size);

	/* rlc ucode */
	rlc_hdr = (const struct rlc_firmware_header_v2_0 *)
		adev->gfx.rlc_fw->data;
	fw_data = (const __le32 *)(adev->gfx.rlc_fw->data +
		le32_to_cpu(rlc_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(rlc_hdr->header.ucode_size_bytes);
	gfx_v10_0_rlc_backdoor_autoload_copy_ucode(adev,
						   FIRMWARE_ID_RLC_G_UCODE,
						   fw_data, fw_size);

	/* mec1 ucode */
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)
		adev->gfx.mec_fw->data;
	fw_data = (const __le32 *) (adev->gfx.mec_fw->data +
		le32_to_cpu(cp_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(cp_hdr->header.ucode_size_bytes) -
		cp_hdr->jt_size * 4;
	gfx_v10_0_rlc_backdoor_autoload_copy_ucode(adev,
						   FIRMWARE_ID_CP_MEC,
						   fw_data, fw_size);
	/* mec2 ucode is not necessary if mec2 ucode is same as mec1 */
}
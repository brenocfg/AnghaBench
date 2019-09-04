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
struct TYPE_8__ {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {TYPE_4__ header; } ;
struct TYPE_7__ {int /*<<< orphan*/  mec2_fw_version; TYPE_2__* mec2_fw; int /*<<< orphan*/  mec_fw_version; TYPE_1__* mec_fw; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_gfx_hdr (TYPE_4__*) ; 
 int /*<<< orphan*/  gfx_v8_0_cp_compute_enable (struct amdgpu_device*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mmCP_MEC_ME1_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_MEC_ME1_UCODE_DATA ; 
 int /*<<< orphan*/  mmCP_MEC_ME2_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_MEC_ME2_UCODE_DATA ; 

__attribute__((used)) static int gfx_v8_0_cp_compute_load_microcode(struct amdgpu_device *adev)
{
	const struct gfx_firmware_header_v1_0 *mec_hdr;
	const __le32 *fw_data;
	unsigned i, fw_size;

	if (!adev->gfx.mec_fw)
		return -EINVAL;

	gfx_v8_0_cp_compute_enable(adev, false);

	mec_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	amdgpu_ucode_print_gfx_hdr(&mec_hdr->header);

	fw_data = (const __le32 *)
		(adev->gfx.mec_fw->data +
		 le32_to_cpu(mec_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(mec_hdr->header.ucode_size_bytes) / 4;

	/* MEC1 */
	WREG32(mmCP_MEC_ME1_UCODE_ADDR, 0);
	for (i = 0; i < fw_size; i++)
		WREG32(mmCP_MEC_ME1_UCODE_DATA, le32_to_cpup(fw_data+i));
	WREG32(mmCP_MEC_ME1_UCODE_ADDR, adev->gfx.mec_fw_version);

	/* Loading MEC2 firmware is only necessary if MEC2 should run different microcode than MEC1. */
	if (adev->gfx.mec2_fw) {
		const struct gfx_firmware_header_v1_0 *mec2_hdr;

		mec2_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec2_fw->data;
		amdgpu_ucode_print_gfx_hdr(&mec2_hdr->header);

		fw_data = (const __le32 *)
			(adev->gfx.mec2_fw->data +
			 le32_to_cpu(mec2_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(mec2_hdr->header.ucode_size_bytes) / 4;

		WREG32(mmCP_MEC_ME2_UCODE_ADDR, 0);
		for (i = 0; i < fw_size; i++)
			WREG32(mmCP_MEC_ME2_UCODE_DATA, le32_to_cpup(fw_data+i));
		WREG32(mmCP_MEC_ME2_UCODE_ADDR, adev->gfx.mec2_fw_version);
	}

	return 0;
}
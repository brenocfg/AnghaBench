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
typedef  unsigned int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {TYPE_5__ header; } ;
struct TYPE_9__ {TYPE_3__* me_fw; TYPE_2__* ce_fw; TYPE_1__* pfp_fw; } ;
struct amdgpu_device {TYPE_4__ gfx; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_gfx_hdr (TYPE_5__*) ; 
 int /*<<< orphan*/  gfx_v6_0_cp_gfx_enable (struct amdgpu_device*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_CE_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_CE_UCODE_DATA ; 
 int /*<<< orphan*/  mmCP_ME_RAM_DATA ; 
 int /*<<< orphan*/  mmCP_ME_RAM_RADDR ; 
 int /*<<< orphan*/  mmCP_ME_RAM_WADDR ; 
 int /*<<< orphan*/  mmCP_PFP_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_PFP_UCODE_DATA ; 

__attribute__((used)) static int gfx_v6_0_cp_gfx_load_microcode(struct amdgpu_device *adev)
{
	unsigned i;
	const struct gfx_firmware_header_v1_0 *pfp_hdr;
	const struct gfx_firmware_header_v1_0 *ce_hdr;
	const struct gfx_firmware_header_v1_0 *me_hdr;
	const __le32 *fw_data;
	u32 fw_size;

	if (!adev->gfx.me_fw || !adev->gfx.pfp_fw || !adev->gfx.ce_fw)
		return -EINVAL;

	gfx_v6_0_cp_gfx_enable(adev, false);
	pfp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
	ce_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
	me_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;

	amdgpu_ucode_print_gfx_hdr(&pfp_hdr->header);
	amdgpu_ucode_print_gfx_hdr(&ce_hdr->header);
	amdgpu_ucode_print_gfx_hdr(&me_hdr->header);

	/* PFP */
	fw_data = (const __le32 *)
		(adev->gfx.pfp_fw->data + le32_to_cpu(pfp_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(pfp_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_PFP_UCODE_ADDR, 0);
	for (i = 0; i < fw_size; i++)
		WREG32(mmCP_PFP_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_PFP_UCODE_ADDR, 0);

	/* CE */
	fw_data = (const __le32 *)
		(adev->gfx.ce_fw->data + le32_to_cpu(ce_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(ce_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_CE_UCODE_ADDR, 0);
	for (i = 0; i < fw_size; i++)
		WREG32(mmCP_CE_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_CE_UCODE_ADDR, 0);

	/* ME */
	fw_data = (const __be32 *)
		(adev->gfx.me_fw->data + le32_to_cpu(me_hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(me_hdr->header.ucode_size_bytes) / 4;
	WREG32(mmCP_ME_RAM_WADDR, 0);
	for (i = 0; i < fw_size; i++)
		WREG32(mmCP_ME_RAM_DATA, le32_to_cpup(fw_data++));
	WREG32(mmCP_ME_RAM_WADDR, 0);

	WREG32(mmCP_PFP_UCODE_ADDR, 0);
	WREG32(mmCP_CE_UCODE_ADDR, 0);
	WREG32(mmCP_ME_RAM_WADDR, 0);
	WREG32(mmCP_ME_RAM_RADDR, 0);
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct vram_usagebyfirmware_v2_1 {int /*<<< orphan*/  used_by_driver_in_kb; int /*<<< orphan*/  used_by_firmware_in_kb; int /*<<< orphan*/  start_address_in_kb; } ;
struct atom_context {int scratch_size_bytes; int /*<<< orphan*/  scratch; scalar_t__ bios; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ start_offset; } ;
struct TYPE_3__ {struct atom_context* atom_context; } ;
struct amdgpu_device {TYPE_2__ fw_vram_usage; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int ATOM_VRAM_BLOCK_SRIOV_MSG_SHARE_RESERVATION ; 
 scalar_t__ ATOM_VRAM_OPERATION_FLAGS_MASK ; 
 int ATOM_VRAM_OPERATION_FLAGS_SHIFT ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ amdgpu_atom_parse_data_header (struct atom_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vram_usagebyfirmware ; 

int amdgpu_atomfirmware_allocate_fb_scratch(struct amdgpu_device *adev)
{
	struct atom_context *ctx = adev->mode_info.atom_context;
	int index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						vram_usagebyfirmware);
	struct vram_usagebyfirmware_v2_1 *	firmware_usage;
	uint32_t start_addr, size;
	uint16_t data_offset;
	int usage_bytes = 0;

	if (amdgpu_atom_parse_data_header(ctx, index, NULL, NULL, NULL, &data_offset)) {
		firmware_usage = (struct vram_usagebyfirmware_v2_1 *)(ctx->bios + data_offset);
		DRM_DEBUG("atom firmware requested %08x %dkb fw %dkb drv\n",
			  le32_to_cpu(firmware_usage->start_address_in_kb),
			  le16_to_cpu(firmware_usage->used_by_firmware_in_kb),
			  le16_to_cpu(firmware_usage->used_by_driver_in_kb));

		start_addr = le32_to_cpu(firmware_usage->start_address_in_kb);
		size = le16_to_cpu(firmware_usage->used_by_firmware_in_kb);

		if ((uint32_t)(start_addr & ATOM_VRAM_OPERATION_FLAGS_MASK) ==
			(uint32_t)(ATOM_VRAM_BLOCK_SRIOV_MSG_SHARE_RESERVATION <<
			ATOM_VRAM_OPERATION_FLAGS_SHIFT)) {
			/* Firmware request VRAM reservation for SR-IOV */
			adev->fw_vram_usage.start_offset = (start_addr &
				(~ATOM_VRAM_OPERATION_FLAGS_MASK)) << 10;
			adev->fw_vram_usage.size = size << 10;
			/* Use the default scratch size */
			usage_bytes = 0;
		} else {
			usage_bytes = le16_to_cpu(firmware_usage->used_by_driver_in_kb) << 10;
		}
	}
	ctx->scratch_size_bytes = 0;
	if (usage_bytes == 0)
		usage_bytes = 20 * 1024;
	/* allocate some scratch memory */
	ctx->scratch = kzalloc(usage_bytes, GFP_KERNEL);
	if (!ctx->scratch)
		return -ENOMEM;
	ctx->scratch_size_bytes = usage_bytes;
	return 0;
}
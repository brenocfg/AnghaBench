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
typedef  scalar_t__ uint16_t ;
struct atom_firmware_info_v3_1 {int /*<<< orphan*/  firmware_capability; } ;
struct TYPE_3__ {TYPE_2__* atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_4__ {scalar_t__ bios; } ;

/* Variables and functions */
 int ATOM_FIRMWARE_CAP_GPU_VIRTUALIZATION ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int /*<<< orphan*/  firmwareinfo ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

bool amdgpu_atomfirmware_gpu_supports_virtualization(struct amdgpu_device *adev)
{
	int index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						firmwareinfo);
	uint16_t data_offset;

	if (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, NULL,
					  NULL, NULL, &data_offset)) {
		struct atom_firmware_info_v3_1 *firmware_info =
			(struct atom_firmware_info_v3_1 *)(adev->mode_info.atom_context->bios +
							   data_offset);

		if (le32_to_cpu(firmware_info->firmware_capability) &
		    ATOM_FIRMWARE_CAP_GPU_VIRTUALIZATION)
			return true;
	}
	return false;
}
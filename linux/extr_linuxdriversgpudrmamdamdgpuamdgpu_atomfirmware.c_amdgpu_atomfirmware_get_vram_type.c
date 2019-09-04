#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vram_type; } ;
union umc_info {TYPE_2__ v31; } ;
struct TYPE_4__ {int memorytype; } ;
union igp_info {TYPE_1__ v11; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct amdgpu_mode_info {TYPE_3__* atom_context; } ;
struct amdgpu_device {int flags; struct amdgpu_mode_info mode_info; } ;
struct TYPE_6__ {scalar_t__ bios; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_3__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int convert_atom_mem_type_to_vram_type (struct amdgpu_device*,int) ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,union umc_info*) ; 
 union umc_info* integratedsysteminfo ; 

int amdgpu_atomfirmware_get_vram_type(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	u16 data_offset, size;
	union igp_info *igp_info;
	union umc_info *umc_info;
	u8 frev, crev;
	u8 mem_type;

	if (adev->flags & AMD_IS_APU)
		index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						    integratedsysteminfo);
	else
		index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						    umc_info);
	if (amdgpu_atom_parse_data_header(mode_info->atom_context,
					  index, &size,
					  &frev, &crev, &data_offset)) {
		if (adev->flags & AMD_IS_APU) {
			igp_info = (union igp_info *)
				(mode_info->atom_context->bios + data_offset);
			switch (crev) {
			case 11:
				mem_type = igp_info->v11.memorytype;
				return convert_atom_mem_type_to_vram_type(adev, mem_type);
			default:
				return 0;
			}
		} else {
			umc_info = (union umc_info *)
				(mode_info->atom_context->bios + data_offset);
			switch (crev) {
			case 1:
				mem_type = umc_info->v31.vram_type;
				return convert_atom_mem_type_to_vram_type(adev, mem_type);
			default:
				return 0;
			}
		}
	}

	return 0;
}
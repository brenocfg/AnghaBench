#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* vram_module; } ;
struct TYPE_9__ {TYPE_2__* vram_module; } ;
union vram_info {TYPE_5__ v24; TYPE_3__ v23; } ;
struct TYPE_7__ {int memorytype; } ;
union igp_info {TYPE_1__ v11; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct amdgpu_mode_info {TYPE_6__* atom_context; } ;
struct amdgpu_device {int flags; struct amdgpu_mode_info mode_info; } ;
struct TYPE_12__ {scalar_t__ bios; } ;
struct TYPE_10__ {int memory_type; } ;
struct TYPE_8__ {int memory_type; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_6__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int convert_atom_mem_type_to_vram_type (struct amdgpu_device*,int) ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,union vram_info*) ; 
 union vram_info* integratedsysteminfo ; 

int amdgpu_atomfirmware_get_vram_type(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	u16 data_offset, size;
	union igp_info *igp_info;
	union vram_info *vram_info;
	u8 frev, crev;
	u8 mem_type;

	if (adev->flags & AMD_IS_APU)
		index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						    integratedsysteminfo);
	else
		index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						    vram_info);
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
			vram_info = (union vram_info *)
				(mode_info->atom_context->bios + data_offset);
			switch (crev) {
			case 3:
				mem_type = vram_info->v23.vram_module[0].memory_type;
				return convert_atom_mem_type_to_vram_type(adev, mem_type);
			case 4:
				mem_type = vram_info->v24.vram_module[0].memory_type;
				return convert_atom_mem_type_to_vram_type(adev, mem_type);
			default:
				return 0;
			}
		}
	}

	return 0;
}
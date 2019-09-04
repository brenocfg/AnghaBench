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
struct TYPE_3__ {int ucUMAChannelNumber; } ;
union igp_info {TYPE_1__ info_8; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct amdgpu_mode_info {TYPE_2__* atom_context; } ;
struct amdgpu_device {struct amdgpu_mode_info mode_info; } ;
struct TYPE_4__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntegratedSystemInfo ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_2__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 

int amdgpu_atombios_get_vram_width(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	u16 data_offset, size;
	union igp_info *igp_info;
	u8 frev, crev;

	/* get any igp specific overrides */
	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		igp_info = (union igp_info *)
			(mode_info->atom_context->bios + data_offset);
		switch (crev) {
		case 8:
		case 9:
			return igp_info->info_8.ucUMAChannelNumber * 64;
		default:
			return 0;
		}
	}

	return 0;
}
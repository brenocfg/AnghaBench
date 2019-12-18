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
struct TYPE_3__ {int /*<<< orphan*/  umc_config; } ;
union umc_info {TYPE_1__ v31; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct amdgpu_mode_info {TYPE_2__* atom_context; } ;
struct amdgpu_device {struct amdgpu_mode_info mode_info; } ;
struct TYPE_4__ {scalar_t__ bios; } ;

/* Variables and functions */
 int UMC_CONFIG__DEFAULT_MEM_ECC_ENABLE ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_2__*,int,scalar_t__*,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,union umc_info*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

bool amdgpu_atomfirmware_mem_ecc_supported(struct amdgpu_device *adev)
{
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	u16 data_offset, size;
	union umc_info *umc_info;
	u8 frev, crev;
	bool ecc_default_enabled = false;

	index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
			umc_info);

	if (amdgpu_atom_parse_data_header(mode_info->atom_context,
				index, &size, &frev, &crev, &data_offset)) {
		/* support umc_info 3.1+ */
		if ((frev == 3 && crev >= 1) || (frev > 3)) {
			umc_info = (union umc_info *)
				(mode_info->atom_context->bios + data_offset);
			ecc_default_enabled =
				(le32_to_cpu(umc_info->v31.umc_config) &
				 UMC_CONFIG__DEFAULT_MEM_ECC_ENABLE) ? true : false;
		}
	}

	return ecc_default_enabled;
}
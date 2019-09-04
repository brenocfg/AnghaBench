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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct si_mc_reg_table {scalar_t__ last; scalar_t__ num_entries; TYPE_3__* mc_reg_table_entry; TYPE_2__* mc_reg_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  vram_type; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;
struct TYPE_6__ {int* mc_data; } ;
struct TYPE_5__ {int s1; void* s0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_VRAM_TYPE_GDDR5 ; 
 int EINVAL ; 
 void* MC_PMG_AUTO_CMD ; 
 void* MC_PMG_CMD_EMRS ; 
 void* MC_PMG_CMD_MRS ; 
 void* MC_PMG_CMD_MRS1 ; 
#define  MC_SEQ_MISC1 129 
 void* MC_SEQ_PMG_CMD_EMRS_LP ; 
 void* MC_SEQ_PMG_CMD_MRS1_LP ; 
 void* MC_SEQ_PMG_CMD_MRS_LP ; 
#define  MC_SEQ_RESERVE_M 128 
 int RREG32 (void*) ; 
 scalar_t__ SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE ; 

__attribute__((used)) static int si_set_mc_special_registers(struct amdgpu_device *adev,
				       struct si_mc_reg_table *table)
{
	u8 i, j, k;
	u32 temp_reg;

	for (i = 0, j = table->last; i < table->last; i++) {
		if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
			return -EINVAL;
		switch (table->mc_reg_address[i].s1) {
		case MC_SEQ_MISC1:
			temp_reg = RREG32(MC_PMG_CMD_EMRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_EMRS;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_EMRS_LP;
			for (k = 0; k < table->num_entries; k++)
				table->mc_reg_table_entry[k].mc_data[j] =
					((temp_reg & 0xffff0000)) |
					((table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16);
			j++;

			if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
				return -EINVAL;
			temp_reg = RREG32(MC_PMG_CMD_MRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS_LP;
			for (k = 0; k < table->num_entries; k++) {
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
				if (adev->gmc.vram_type != AMDGPU_VRAM_TYPE_GDDR5)
					table->mc_reg_table_entry[k].mc_data[j] |= 0x100;
			}
			j++;

			if (adev->gmc.vram_type != AMDGPU_VRAM_TYPE_GDDR5) {
				if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
					return -EINVAL;
				table->mc_reg_address[j].s1 = MC_PMG_AUTO_CMD;
				table->mc_reg_address[j].s0 = MC_PMG_AUTO_CMD;
				for (k = 0; k < table->num_entries; k++)
					table->mc_reg_table_entry[k].mc_data[j] =
						(table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16;
				j++;
			}
			break;
		case MC_SEQ_RESERVE_M:
			temp_reg = RREG32(MC_PMG_CMD_MRS1);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS1;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS1_LP;
			for(k = 0; k < table->num_entries; k++)
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
			j++;
			break;
		default:
			break;
		}
	}

	table->last = j;

	return 0;
}
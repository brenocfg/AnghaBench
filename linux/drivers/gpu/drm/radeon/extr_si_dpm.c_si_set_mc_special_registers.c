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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct si_mc_reg_table {scalar_t__ last; scalar_t__ num_entries; TYPE_2__* mc_reg_table_entry; TYPE_1__* mc_reg_address; } ;
struct rv7xx_power_info {int /*<<< orphan*/  mem_gddr5; } ;
struct radeon_device {int dummy; } ;
struct TYPE_4__ {int* mc_data; } ;
struct TYPE_3__ {int s1; int s0; } ;

/* Variables and functions */
 int EINVAL ; 
 int MC_PMG_AUTO_CMD ; 
 int MC_PMG_CMD_EMRS ; 
 int MC_PMG_CMD_MRS ; 
 int MC_PMG_CMD_MRS1 ; 
#define  MC_SEQ_MISC1 129 
 int MC_SEQ_PMG_CMD_EMRS_LP ; 
 int MC_SEQ_PMG_CMD_MRS1_LP ; 
 int MC_SEQ_PMG_CMD_MRS_LP ; 
#define  MC_SEQ_RESERVE_M 128 
 int RREG32 (int) ; 
 scalar_t__ SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int si_set_mc_special_registers(struct radeon_device *rdev,
				       struct si_mc_reg_table *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u8 i, j, k;
	u32 temp_reg;

	for (i = 0, j = table->last; i < table->last; i++) {
		if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
			return -EINVAL;
		switch (table->mc_reg_address[i].s1 << 2) {
		case MC_SEQ_MISC1:
			temp_reg = RREG32(MC_PMG_CMD_EMRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_EMRS >> 2;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_EMRS_LP >> 2;
			for (k = 0; k < table->num_entries; k++)
				table->mc_reg_table_entry[k].mc_data[j] =
					((temp_reg & 0xffff0000)) |
					((table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16);
			j++;
			if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
				return -EINVAL;

			temp_reg = RREG32(MC_PMG_CMD_MRS);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS >> 2;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS_LP >> 2;
			for (k = 0; k < table->num_entries; k++) {
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
				if (!pi->mem_gddr5)
					table->mc_reg_table_entry[k].mc_data[j] |= 0x100;
			}
			j++;
			if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
				return -EINVAL;

			if (!pi->mem_gddr5) {
				table->mc_reg_address[j].s1 = MC_PMG_AUTO_CMD >> 2;
				table->mc_reg_address[j].s0 = MC_PMG_AUTO_CMD >> 2;
				for (k = 0; k < table->num_entries; k++)
					table->mc_reg_table_entry[k].mc_data[j] =
						(table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16;
				j++;
				if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
					return -EINVAL;
			}
			break;
		case MC_SEQ_RESERVE_M:
			temp_reg = RREG32(MC_PMG_CMD_MRS1);
			table->mc_reg_address[j].s1 = MC_PMG_CMD_MRS1 >> 2;
			table->mc_reg_address[j].s0 = MC_SEQ_PMG_CMD_MRS1_LP >> 2;
			for(k = 0; k < table->num_entries; k++)
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
			j++;
			if (j >= SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE)
				return -EINVAL;
			break;
		default:
			break;
		}
	}

	table->last = j;

	return 0;
}
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
typedef  size_t u8 ;
typedef  int u32 ;
struct radeon_device {TYPE_1__* pdev; } ;
struct ci_mc_reg_table {size_t last; size_t num_entries; TYPE_3__* mc_reg_table_entry; TYPE_2__* mc_reg_address; } ;
struct TYPE_6__ {int mclk_max; int* mc_data; } ;
struct TYPE_5__ {int s1; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MC_SEQ_CAS_TIMING 133 
 int /*<<< orphan*/  MC_SEQ_IO_DEBUG_DATA ; 
 int /*<<< orphan*/  MC_SEQ_IO_DEBUG_INDEX ; 
 int /*<<< orphan*/  MC_SEQ_MISC0 ; 
#define  MC_SEQ_MISC1 132 
#define  MC_SEQ_MISC_TIMING 131 
#define  MC_SEQ_WR_CTL_2 130 
#define  MC_SEQ_WR_CTL_D0 129 
#define  MC_SEQ_WR_CTL_D1 128 
 int RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ci_register_patching_mc_seq(struct radeon_device *rdev,
				       struct ci_mc_reg_table *table)
{
	u8 i, k;
	u32 tmp;
	bool patch;

	tmp = RREG32(MC_SEQ_MISC0);
	patch = ((tmp & 0x0000f00) == 0x300) ? true : false;

	if (patch &&
	    ((rdev->pdev->device == 0x67B0) ||
	     (rdev->pdev->device == 0x67B1))) {
		for (i = 0; i < table->last; i++) {
			if (table->last >= SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE)
				return -EINVAL;
			switch(table->mc_reg_address[i].s1 >> 2) {
			case MC_SEQ_MISC1:
				for (k = 0; k < table->num_entries; k++) {
					if ((table->mc_reg_table_entry[k].mclk_max == 125000) ||
					    (table->mc_reg_table_entry[k].mclk_max == 137500))
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFFFFFF8) |
							0x00000007;
				}
				break;
			case MC_SEQ_WR_CTL_D0:
				for (k = 0; k < table->num_entries; k++) {
					if ((table->mc_reg_table_entry[k].mclk_max == 125000) ||
					    (table->mc_reg_table_entry[k].mclk_max == 137500))
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFFF0F00) |
							0x0000D0DD;
				}
				break;
			case MC_SEQ_WR_CTL_D1:
				for (k = 0; k < table->num_entries; k++) {
					if ((table->mc_reg_table_entry[k].mclk_max == 125000) ||
					    (table->mc_reg_table_entry[k].mclk_max == 137500))
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFFF0F00) |
							0x0000D0DD;
				}
				break;
			case MC_SEQ_WR_CTL_2:
				for (k = 0; k < table->num_entries; k++) {
					if ((table->mc_reg_table_entry[k].mclk_max == 125000) ||
					    (table->mc_reg_table_entry[k].mclk_max == 137500))
						table->mc_reg_table_entry[k].mc_data[i] = 0;
				}
				break;
			case MC_SEQ_CAS_TIMING:
				for (k = 0; k < table->num_entries; k++) {
					if (table->mc_reg_table_entry[k].mclk_max == 125000)
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFE0FE0F) |
							0x000C0140;
					else if (table->mc_reg_table_entry[k].mclk_max == 137500)
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFE0FE0F) |
							0x000C0150;
				}
				break;
			case MC_SEQ_MISC_TIMING:
				for (k = 0; k < table->num_entries; k++) {
					if (table->mc_reg_table_entry[k].mclk_max == 125000)
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFFFFFE0) |
							0x00000030;
					else if (table->mc_reg_table_entry[k].mclk_max == 137500)
						table->mc_reg_table_entry[k].mc_data[i] =
							(table->mc_reg_table_entry[k].mc_data[i] & 0xFFFFFFE0) |
							0x00000035;
				}
				break;
			default:
				break;
			}
		}

		WREG32(MC_SEQ_IO_DEBUG_INDEX, 3);
		tmp = RREG32(MC_SEQ_IO_DEBUG_DATA);
		tmp = (tmp & 0xFFF8FFFF) | (1 << 16);
		WREG32(MC_SEQ_IO_DEBUG_INDEX, 3);
		WREG32(MC_SEQ_IO_DEBUG_DATA, tmp);
	}

	return 0;
}
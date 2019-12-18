#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vegam_smumgr {TYPE_4__* range_table; } ;
struct pp_hwmgr {scalar_t__ adev; scalar_t__ smu_backend; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_2__ member_0; } ;
struct pp_atom_ctrl_sclk_range_table {TYPE_3__* entry; TYPE_1__ member_0; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_15__ {size_t fcw_trans_lower; size_t postdiv; size_t fcw_trans_upper; size_t fcw_pcc; int /*<<< orphan*/  vco_setting; } ;
struct TYPE_14__ {TYPE_5__* SclkFcwRangeTable; } ;
struct TYPE_13__ {size_t postdiv; size_t fcw_pcc; size_t fcw_trans_upper; size_t fcw_trans_lower; int /*<<< orphan*/  vco_setting; } ;
struct TYPE_12__ {size_t trans_lower_frequency; size_t trans_upper_frequency; } ;
struct TYPE_11__ {size_t ucPostdiv; size_t usFcw_pcc; size_t usFcw_trans_upper; size_t usRcw_trans_lower; int /*<<< orphan*/  ucVco_setting; } ;
typedef  TYPE_6__ SMU75_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_US (size_t) ; 
 size_t NUM_SCLK_RANGE ; 
 TYPE_8__* Range_Table ; 
 size_t amdgpu_asic_get_xclk (struct amdgpu_device*) ; 
 scalar_t__ atomctrl_get_smc_sclk_range_table (struct pp_hwmgr*,struct pp_atom_ctrl_sclk_range_table*) ; 

__attribute__((used)) static void vegam_get_sclk_range_table(struct pp_hwmgr *hwmgr,
				   SMU75_Discrete_DpmTable  *table)
{
	struct vegam_smumgr *smu_data = (struct vegam_smumgr *)(hwmgr->smu_backend);
	uint32_t i, ref_clk;

	struct pp_atom_ctrl_sclk_range_table range_table_from_vbios = { { {0} } };

	ref_clk = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);

	if (0 == atomctrl_get_smc_sclk_range_table(hwmgr, &range_table_from_vbios)) {
		for (i = 0; i < NUM_SCLK_RANGE; i++) {
			table->SclkFcwRangeTable[i].vco_setting =
					range_table_from_vbios.entry[i].ucVco_setting;
			table->SclkFcwRangeTable[i].postdiv =
					range_table_from_vbios.entry[i].ucPostdiv;
			table->SclkFcwRangeTable[i].fcw_pcc =
					range_table_from_vbios.entry[i].usFcw_pcc;

			table->SclkFcwRangeTable[i].fcw_trans_upper =
					range_table_from_vbios.entry[i].usFcw_trans_upper;
			table->SclkFcwRangeTable[i].fcw_trans_lower =
					range_table_from_vbios.entry[i].usRcw_trans_lower;

			CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_pcc);
			CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_upper);
			CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_lower);
		}
		return;
	}

	for (i = 0; i < NUM_SCLK_RANGE; i++) {
		smu_data->range_table[i].trans_lower_frequency =
				(ref_clk * Range_Table[i].fcw_trans_lower) >> Range_Table[i].postdiv;
		smu_data->range_table[i].trans_upper_frequency =
				(ref_clk * Range_Table[i].fcw_trans_upper) >> Range_Table[i].postdiv;

		table->SclkFcwRangeTable[i].vco_setting = Range_Table[i].vco_setting;
		table->SclkFcwRangeTable[i].postdiv = Range_Table[i].postdiv;
		table->SclkFcwRangeTable[i].fcw_pcc = Range_Table[i].fcw_pcc;

		table->SclkFcwRangeTable[i].fcw_trans_upper = Range_Table[i].fcw_trans_upper;
		table->SclkFcwRangeTable[i].fcw_trans_lower = Range_Table[i].fcw_trans_lower;

		CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_pcc);
		CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_upper);
		CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_lower);
	}
}
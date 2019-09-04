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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
struct pp_atom_ctrl_sclk_range_table {TYPE_1__* entry; } ;
struct TYPE_6__ {int ucSclkEntryNum; TYPE_2__* asSclkFcwRangeEntry; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucRcw_trans_lower; int /*<<< orphan*/  ucFcw_trans_upper; int /*<<< orphan*/  ucFcw_pcc; int /*<<< orphan*/  ucPostdiv; int /*<<< orphan*/  ucVco_setting; } ;
struct TYPE_4__ {void* usRcw_trans_lower; void* usFcw_trans_upper; void* usFcw_pcc; int /*<<< orphan*/  ucPostdiv; int /*<<< orphan*/  ucVco_setting; } ;
typedef  TYPE_3__ ATOM_SMU_INFO_V2_1 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_Info ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int atomctrl_get_smc_sclk_range_table(struct pp_hwmgr *hwmgr, struct pp_atom_ctrl_sclk_range_table *table)
{

	int i;
	u8 frev, crev;
	u16 size;

	ATOM_SMU_INFO_V2_1 *psmu_info =
		(ATOM_SMU_INFO_V2_1 *)smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, SMU_Info),
			&size, &frev, &crev);


	for (i = 0; i < psmu_info->ucSclkEntryNum; i++) {
		table->entry[i].ucVco_setting = psmu_info->asSclkFcwRangeEntry[i].ucVco_setting;
		table->entry[i].ucPostdiv = psmu_info->asSclkFcwRangeEntry[i].ucPostdiv;
		table->entry[i].usFcw_pcc =
			le16_to_cpu(psmu_info->asSclkFcwRangeEntry[i].ucFcw_pcc);
		table->entry[i].usFcw_trans_upper =
			le16_to_cpu(psmu_info->asSclkFcwRangeEntry[i].ucFcw_trans_upper);
		table->entry[i].usRcw_trans_lower =
			le16_to_cpu(psmu_info->asSclkFcwRangeEntry[i].ucRcw_trans_lower);
	}

	return 0;
}
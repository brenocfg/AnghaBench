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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
typedef  int /*<<< orphan*/  pp_atomctrl_mc_reg_table ;
struct TYPE_3__ {int ucTableFormatRevision; } ;
struct TYPE_4__ {scalar_t__ ucNumOfVRAMModule; int /*<<< orphan*/  usMemClkPatchTblOffset; TYPE_1__ sHeader; } ;
typedef  TYPE_2__ ATOM_VRAM_INFO_HEADER_V2_1 ;
typedef  int /*<<< orphan*/  ATOM_INIT_REG_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRAM_Info ; 
 int atomctrl_retrieve_ac_timing (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int atomctrl_set_mc_reg_address_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int atomctrl_initialize_mc_reg_table(
		struct pp_hwmgr *hwmgr,
		uint8_t module_index,
		pp_atomctrl_mc_reg_table *table)
{
	ATOM_VRAM_INFO_HEADER_V2_1 *vram_info;
	ATOM_INIT_REG_BLOCK *reg_block;
	int result = 0;
	u8 frev, crev;
	u16 size;

	vram_info = (ATOM_VRAM_INFO_HEADER_V2_1 *)
		smu_atom_get_data_table(hwmgr->adev,
				GetIndexIntoMasterTable(DATA, VRAM_Info), &size, &frev, &crev);

	if (module_index >= vram_info->ucNumOfVRAMModule) {
		pr_err("Invalid VramInfo table.");
		result = -1;
	} else if (vram_info->sHeader.ucTableFormatRevision < 2) {
		pr_err("Invalid VramInfo table.");
		result = -1;
	}

	if (0 == result) {
		reg_block = (ATOM_INIT_REG_BLOCK *)
			((uint8_t *)vram_info + le16_to_cpu(vram_info->usMemClkPatchTblOffset));
		result = atomctrl_set_mc_reg_address_table(reg_block, table);
	}

	if (0 == result) {
		result = atomctrl_retrieve_ac_timing(module_index,
					reg_block, table);
	}

	return result;
}
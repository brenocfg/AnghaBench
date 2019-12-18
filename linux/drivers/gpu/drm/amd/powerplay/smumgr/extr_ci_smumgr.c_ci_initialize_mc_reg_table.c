#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ smu_backend; } ;
struct ci_mc_reg_table {int dummy; } ;
struct ci_smumgr {struct ci_mc_reg_table mc_reg_table; } ;
typedef  int /*<<< orphan*/  pp_atomctrl_mc_reg_table ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int atomctrl_initialize_mc_reg_table (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ci_copy_vbios_smc_reg_table (int /*<<< orphan*/ *,struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  ci_get_memory_modile_index (struct pp_hwmgr*) ; 
 int ci_set_mc_special_registers (struct pp_hwmgr*,struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  ci_set_s0_mc_reg_index (struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  ci_set_valid_flag (struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_PMG_CMD_EMRS ; 
 int /*<<< orphan*/  mmMC_PMG_CMD_MRS ; 
 int /*<<< orphan*/  mmMC_PMG_CMD_MRS1 ; 
 int /*<<< orphan*/  mmMC_PMG_CMD_MRS2 ; 
 int /*<<< orphan*/  mmMC_SEQ_CAS_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_CAS_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_DLL_STBY ; 
 int /*<<< orphan*/  mmMC_SEQ_DLL_STBY_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_G5PDX_CMD0 ; 
 int /*<<< orphan*/  mmMC_SEQ_G5PDX_CMD0_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_G5PDX_CMD1 ; 
 int /*<<< orphan*/  mmMC_SEQ_G5PDX_CMD1_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_G5PDX_CTRL ; 
 int /*<<< orphan*/  mmMC_SEQ_G5PDX_CTRL_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC_TIMING2 ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC_TIMING2_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_CMD_EMRS_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_CMD_MRS1_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_CMD_MRS2_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_CMD_MRS_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_DVS_CMD ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_DVS_CMD_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_DVS_CTL ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_DVS_CTL_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_PMG_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_RAS_TIMING ; 
 int /*<<< orphan*/  mmMC_SEQ_RAS_TIMING_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D0 ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D0_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D1 ; 
 int /*<<< orphan*/  mmMC_SEQ_RD_CTL_D1_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_2 ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_2_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_D0 ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_D0_LP ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_D1 ; 
 int /*<<< orphan*/  mmMC_SEQ_WR_CTL_D1_LP ; 

__attribute__((used)) static int ci_initialize_mc_reg_table(struct pp_hwmgr *hwmgr)
{
	int result;
	struct ci_smumgr *smu_data = (struct ci_smumgr *)(hwmgr->smu_backend);
	pp_atomctrl_mc_reg_table *table;
	struct ci_mc_reg_table *ni_table = &smu_data->mc_reg_table;
	uint8_t module_index = ci_get_memory_modile_index(hwmgr);

	table = kzalloc(sizeof(pp_atomctrl_mc_reg_table), GFP_KERNEL);

	if (NULL == table)
		return -ENOMEM;

	/* Program additional LP registers that are no longer programmed by VBIOS */
	cgs_write_register(hwmgr->device, mmMC_SEQ_RAS_TIMING_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_RAS_TIMING));
	cgs_write_register(hwmgr->device, mmMC_SEQ_CAS_TIMING_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_CAS_TIMING));
	cgs_write_register(hwmgr->device, mmMC_SEQ_DLL_STBY_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_DLL_STBY));
	cgs_write_register(hwmgr->device, mmMC_SEQ_G5PDX_CMD0_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_G5PDX_CMD0));
	cgs_write_register(hwmgr->device, mmMC_SEQ_G5PDX_CMD1_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_G5PDX_CMD1));
	cgs_write_register(hwmgr->device, mmMC_SEQ_G5PDX_CTRL_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_G5PDX_CTRL));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_DVS_CMD_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_PMG_DVS_CMD));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_DVS_CTL_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_PMG_DVS_CTL));
	cgs_write_register(hwmgr->device, mmMC_SEQ_MISC_TIMING_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_MISC_TIMING));
	cgs_write_register(hwmgr->device, mmMC_SEQ_MISC_TIMING2_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_MISC_TIMING2));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_CMD_EMRS_LP, cgs_read_register(hwmgr->device, mmMC_PMG_CMD_EMRS));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS_LP, cgs_read_register(hwmgr->device, mmMC_PMG_CMD_MRS));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS1_LP, cgs_read_register(hwmgr->device, mmMC_PMG_CMD_MRS1));
	cgs_write_register(hwmgr->device, mmMC_SEQ_WR_CTL_D0_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_WR_CTL_D0));
	cgs_write_register(hwmgr->device, mmMC_SEQ_WR_CTL_D1_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_WR_CTL_D1));
	cgs_write_register(hwmgr->device, mmMC_SEQ_RD_CTL_D0_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_RD_CTL_D0));
	cgs_write_register(hwmgr->device, mmMC_SEQ_RD_CTL_D1_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_RD_CTL_D1));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_TIMING_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_PMG_TIMING));
	cgs_write_register(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS2_LP, cgs_read_register(hwmgr->device, mmMC_PMG_CMD_MRS2));
	cgs_write_register(hwmgr->device, mmMC_SEQ_WR_CTL_2_LP, cgs_read_register(hwmgr->device, mmMC_SEQ_WR_CTL_2));

	result = atomctrl_initialize_mc_reg_table(hwmgr, module_index, table);

	if (0 == result)
		result = ci_copy_vbios_smc_reg_table(table, ni_table);

	if (0 == result) {
		ci_set_s0_mc_reg_index(ni_table);
		result = ci_set_mc_special_registers(hwmgr, ni_table);
	}

	if (0 == result)
		ci_set_valid_flag(ni_table);

	kfree(table);

	return result;
}
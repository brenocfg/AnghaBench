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
typedef  int /*<<< orphan*/  u8 ;
struct radeon_device {int dummy; } ;
struct ci_mc_reg_table {int dummy; } ;
struct ci_power_info {struct ci_mc_reg_table mc_reg_table; } ;
struct atom_mc_reg_table {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MC_PMG_CMD_EMRS ; 
 int /*<<< orphan*/  MC_PMG_CMD_MRS ; 
 int /*<<< orphan*/  MC_PMG_CMD_MRS1 ; 
 int /*<<< orphan*/  MC_PMG_CMD_MRS2 ; 
 int /*<<< orphan*/  MC_SEQ_CAS_TIMING ; 
 int /*<<< orphan*/  MC_SEQ_CAS_TIMING_LP ; 
 int /*<<< orphan*/  MC_SEQ_DLL_STBY ; 
 int /*<<< orphan*/  MC_SEQ_DLL_STBY_LP ; 
 int /*<<< orphan*/  MC_SEQ_G5PDX_CMD0 ; 
 int /*<<< orphan*/  MC_SEQ_G5PDX_CMD0_LP ; 
 int /*<<< orphan*/  MC_SEQ_G5PDX_CMD1 ; 
 int /*<<< orphan*/  MC_SEQ_G5PDX_CMD1_LP ; 
 int /*<<< orphan*/  MC_SEQ_G5PDX_CTRL ; 
 int /*<<< orphan*/  MC_SEQ_G5PDX_CTRL_LP ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING2 ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING2_LP ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_EMRS_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_MRS1_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_MRS2_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_MRS_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_DVS_CMD ; 
 int /*<<< orphan*/  MC_SEQ_PMG_DVS_CMD_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_DVS_CTL ; 
 int /*<<< orphan*/  MC_SEQ_PMG_DVS_CTL_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_TIMING ; 
 int /*<<< orphan*/  MC_SEQ_PMG_TIMING_LP ; 
 int /*<<< orphan*/  MC_SEQ_RAS_TIMING ; 
 int /*<<< orphan*/  MC_SEQ_RAS_TIMING_LP ; 
 int /*<<< orphan*/  MC_SEQ_RD_CTL_D0 ; 
 int /*<<< orphan*/  MC_SEQ_RD_CTL_D0_LP ; 
 int /*<<< orphan*/  MC_SEQ_RD_CTL_D1 ; 
 int /*<<< orphan*/  MC_SEQ_RD_CTL_D1_LP ; 
 int /*<<< orphan*/  MC_SEQ_WR_CTL_2 ; 
 int /*<<< orphan*/  MC_SEQ_WR_CTL_2_LP ; 
 int /*<<< orphan*/  MC_SEQ_WR_CTL_D0 ; 
 int /*<<< orphan*/  MC_SEQ_WR_CTL_D0_LP ; 
 int /*<<< orphan*/  MC_SEQ_WR_CTL_D1 ; 
 int /*<<< orphan*/  MC_SEQ_WR_CTL_D1_LP ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ci_copy_vbios_mc_reg_table (struct atom_mc_reg_table*,struct ci_mc_reg_table*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_register_patching_mc_seq (struct radeon_device*,struct ci_mc_reg_table*) ; 
 int ci_set_mc_special_registers (struct radeon_device*,struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  ci_set_s0_mc_reg_index (struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  ci_set_valid_flag (struct ci_mc_reg_table*) ; 
 int /*<<< orphan*/  kfree (struct atom_mc_reg_table*) ; 
 struct atom_mc_reg_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int radeon_atom_init_mc_reg_table (struct radeon_device*,int /*<<< orphan*/ ,struct atom_mc_reg_table*) ; 
 int /*<<< orphan*/  rv770_get_memory_module_index (struct radeon_device*) ; 

__attribute__((used)) static int ci_initialize_mc_reg_table(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct atom_mc_reg_table *table;
	struct ci_mc_reg_table *ci_table = &pi->mc_reg_table;
	u8 module_index = rv770_get_memory_module_index(rdev);
	int ret;

	table = kzalloc(sizeof(struct atom_mc_reg_table), GFP_KERNEL);
	if (!table)
		return -ENOMEM;

	WREG32(MC_SEQ_RAS_TIMING_LP, RREG32(MC_SEQ_RAS_TIMING));
	WREG32(MC_SEQ_CAS_TIMING_LP, RREG32(MC_SEQ_CAS_TIMING));
	WREG32(MC_SEQ_DLL_STBY_LP, RREG32(MC_SEQ_DLL_STBY));
	WREG32(MC_SEQ_G5PDX_CMD0_LP, RREG32(MC_SEQ_G5PDX_CMD0));
	WREG32(MC_SEQ_G5PDX_CMD1_LP, RREG32(MC_SEQ_G5PDX_CMD1));
	WREG32(MC_SEQ_G5PDX_CTRL_LP, RREG32(MC_SEQ_G5PDX_CTRL));
	WREG32(MC_SEQ_PMG_DVS_CMD_LP, RREG32(MC_SEQ_PMG_DVS_CMD));
	WREG32(MC_SEQ_PMG_DVS_CTL_LP, RREG32(MC_SEQ_PMG_DVS_CTL));
	WREG32(MC_SEQ_MISC_TIMING_LP, RREG32(MC_SEQ_MISC_TIMING));
	WREG32(MC_SEQ_MISC_TIMING2_LP, RREG32(MC_SEQ_MISC_TIMING2));
	WREG32(MC_SEQ_PMG_CMD_EMRS_LP, RREG32(MC_PMG_CMD_EMRS));
	WREG32(MC_SEQ_PMG_CMD_MRS_LP, RREG32(MC_PMG_CMD_MRS));
	WREG32(MC_SEQ_PMG_CMD_MRS1_LP, RREG32(MC_PMG_CMD_MRS1));
	WREG32(MC_SEQ_WR_CTL_D0_LP, RREG32(MC_SEQ_WR_CTL_D0));
	WREG32(MC_SEQ_WR_CTL_D1_LP, RREG32(MC_SEQ_WR_CTL_D1));
	WREG32(MC_SEQ_RD_CTL_D0_LP, RREG32(MC_SEQ_RD_CTL_D0));
	WREG32(MC_SEQ_RD_CTL_D1_LP, RREG32(MC_SEQ_RD_CTL_D1));
	WREG32(MC_SEQ_PMG_TIMING_LP, RREG32(MC_SEQ_PMG_TIMING));
	WREG32(MC_SEQ_PMG_CMD_MRS2_LP, RREG32(MC_PMG_CMD_MRS2));
	WREG32(MC_SEQ_WR_CTL_2_LP, RREG32(MC_SEQ_WR_CTL_2));

	ret = radeon_atom_init_mc_reg_table(rdev, module_index, table);
	if (ret)
		goto init_mc_done;

	ret = ci_copy_vbios_mc_reg_table(table, ci_table);
	if (ret)
		goto init_mc_done;

	ci_set_s0_mc_reg_index(ci_table);

	ret = ci_register_patching_mc_seq(rdev, ci_table);
	if (ret)
		goto init_mc_done;

	ret = ci_set_mc_special_registers(rdev, ci_table);
	if (ret)
		goto init_mc_done;

	ci_set_valid_flag(ci_table);

init_mc_done:
	kfree(table);

	return ret;
}
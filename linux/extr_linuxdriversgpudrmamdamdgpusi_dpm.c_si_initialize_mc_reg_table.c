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
struct si_mc_reg_table {int dummy; } ;
struct si_power_info {struct si_mc_reg_table mc_reg_table; } ;
struct atom_mc_reg_table {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MC_PMG_CMD_EMRS ; 
 int /*<<< orphan*/  MC_PMG_CMD_MRS ; 
 int /*<<< orphan*/  MC_PMG_CMD_MRS1 ; 
 int /*<<< orphan*/  MC_PMG_CMD_MRS2 ; 
 int /*<<< orphan*/  MC_SEQ_CAS_TIMING ; 
 int /*<<< orphan*/  MC_SEQ_CAS_TIMING_LP ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING2 ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING2_LP ; 
 int /*<<< orphan*/  MC_SEQ_MISC_TIMING_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_EMRS_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_MRS1_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_MRS2_LP ; 
 int /*<<< orphan*/  MC_SEQ_PMG_CMD_MRS_LP ; 
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
 int amdgpu_atombios_init_mc_reg_table (struct amdgpu_device*,int /*<<< orphan*/ ,struct atom_mc_reg_table*) ; 
 int /*<<< orphan*/  kfree (struct atom_mc_reg_table*) ; 
 struct atom_mc_reg_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_get_memory_module_index (struct amdgpu_device*) ; 
 int si_copy_vbios_mc_reg_table (struct atom_mc_reg_table*,struct si_mc_reg_table*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int si_set_mc_special_registers (struct amdgpu_device*,struct si_mc_reg_table*) ; 
 int /*<<< orphan*/  si_set_s0_mc_reg_index (struct si_mc_reg_table*) ; 
 int /*<<< orphan*/  si_set_valid_flag (struct si_mc_reg_table*) ; 

__attribute__((used)) static int si_initialize_mc_reg_table(struct amdgpu_device *adev)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	struct atom_mc_reg_table *table;
	struct si_mc_reg_table *si_table = &si_pi->mc_reg_table;
	u8 module_index = rv770_get_memory_module_index(adev);
	int ret;

	table = kzalloc(sizeof(struct atom_mc_reg_table), GFP_KERNEL);
	if (!table)
		return -ENOMEM;

	WREG32(MC_SEQ_RAS_TIMING_LP, RREG32(MC_SEQ_RAS_TIMING));
	WREG32(MC_SEQ_CAS_TIMING_LP, RREG32(MC_SEQ_CAS_TIMING));
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

	ret = amdgpu_atombios_init_mc_reg_table(adev, module_index, table);
	if (ret)
		goto init_mc_done;

	ret = si_copy_vbios_mc_reg_table(table, si_table);
	if (ret)
		goto init_mc_done;

	si_set_s0_mc_reg_index(si_table);

	ret = si_set_mc_special_registers(adev, si_table);
	if (ret)
		goto init_mc_done;

	si_set_valid_flag(si_table);

init_mc_done:
	kfree(table);

	return ret;

}
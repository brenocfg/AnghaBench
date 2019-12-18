#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int mpll_ad_func_cntl; int mpll_ad_func_cntl_2; int mpll_dq_func_cntl; int mpll_dq_func_cntl_2; int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; int mclk_pwrmgt_cntl; int dll_cntl; } ;
struct TYPE_14__ {TYPE_4__ rv770; } ;
struct rv7xx_power_info {scalar_t__ mem_gddr5; scalar_t__ min_vddc_in_table; scalar_t__ acpi_pcie_gen2; scalar_t__ pcie_gen2; scalar_t__ acpi_vddc; TYPE_5__ clk_regs; } ;
struct radeon_device {scalar_t__ family; } ;
struct evergreen_power_info {scalar_t__ dynamic_ac_timing; scalar_t__ acpi_vddci; int /*<<< orphan*/  vddci_voltage_table; scalar_t__ vddci_control; int /*<<< orphan*/  vddc_voltage_table; } ;
struct TYPE_16__ {TYPE_6__* levels; int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {TYPE_7__ ACPIState; TYPE_7__ initialState; } ;
struct TYPE_12__ {scalar_t__ sclk_value; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct TYPE_10__ {scalar_t__ mclk_value; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_DQ_FUNC_CNTL_2; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL_2; void* vMPLL_AD_FUNC_CNTL; } ;
struct TYPE_11__ {TYPE_1__ mclk770; } ;
struct TYPE_15__ {int gen2PCIE; int gen2XSP; int ACIndex; int /*<<< orphan*/  mvdd; TYPE_3__ sclk; TYPE_2__ mclk; int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; } ;
typedef  TYPE_8__ RV770_SMC_STATETABLE ;

/* Variables and functions */
 int BIAS_GEN_PDNB ; 
 int BYPASS ; 
 scalar_t__ CHIP_HEMLOCK ; 
 int MRDCKA0_BYPASS ; 
 int MRDCKA0_PDNB ; 
 int MRDCKA0_RESET ; 
 int MRDCKA1_BYPASS ; 
 int MRDCKA1_PDNB ; 
 int MRDCKA1_RESET ; 
 int MRDCKB0_BYPASS ; 
 int MRDCKB0_PDNB ; 
 int MRDCKB0_RESET ; 
 int MRDCKB1_BYPASS ; 
 int MRDCKB1_PDNB ; 
 int MRDCKB1_RESET ; 
 int MRDCKC0_BYPASS ; 
 int MRDCKC0_PDNB ; 
 int MRDCKC0_RESET ; 
 int MRDCKC1_BYPASS ; 
 int MRDCKC1_PDNB ; 
 int MRDCKC1_RESET ; 
 int MRDCKD0_BYPASS ; 
 int MRDCKD0_PDNB ; 
 int MRDCKD0_RESET ; 
 int MRDCKD1_BYPASS ; 
 int MRDCKD1_PDNB ; 
 int MRDCKD1_RESET ; 
 int PDNB ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int RESET_EN ; 
 int SCLK_MUX_SEL (int) ; 
 int SCLK_MUX_SEL_MASK ; 
 int SPLL_BYPASS_EN ; 
 int SPLL_RESET ; 
 int SPLL_SLEEP ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cypress_populate_mvdd_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cypress_populate_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

int cypress_populate_smc_acpi_state(struct radeon_device *rdev,
				    RV770_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 mpll_ad_func_cntl =
		pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 =
		pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl =
		pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 =
		pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 spll_func_cntl =
		pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 =
		pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 =
		pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 mclk_pwrmgt_cntl =
		pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl =
		pi->clk_regs.rv770.dll_cntl;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	if (pi->acpi_vddc) {
		cypress_populate_voltage_value(rdev,
					       &eg_pi->vddc_voltage_table,
					       pi->acpi_vddc,
					       &table->ACPIState.levels[0].vddc);
		if (pi->pcie_gen2) {
			if (pi->acpi_pcie_gen2)
				table->ACPIState.levels[0].gen2PCIE = 1;
			else
				table->ACPIState.levels[0].gen2PCIE = 0;
		} else
			table->ACPIState.levels[0].gen2PCIE = 0;
		if (pi->acpi_pcie_gen2)
			table->ACPIState.levels[0].gen2XSP = 1;
		else
			table->ACPIState.levels[0].gen2XSP = 0;
	} else {
		cypress_populate_voltage_value(rdev,
					       &eg_pi->vddc_voltage_table,
					       pi->min_vddc_in_table,
					       &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE = 0;
	}

	if (eg_pi->acpi_vddci) {
		if (eg_pi->vddci_control) {
			cypress_populate_voltage_value(rdev,
						       &eg_pi->vddci_voltage_table,
						       eg_pi->acpi_vddci,
						       &table->ACPIState.levels[0].vddci);
		}
	}

	mpll_ad_func_cntl &= ~PDNB;

	mpll_ad_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN;

	if (pi->mem_gddr5)
		mpll_dq_func_cntl &= ~PDNB;
	mpll_dq_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN | BYPASS;

	mclk_pwrmgt_cntl |= (MRDCKA0_RESET |
			     MRDCKA1_RESET |
			     MRDCKB0_RESET |
			     MRDCKB1_RESET |
			     MRDCKC0_RESET |
			     MRDCKC1_RESET |
			     MRDCKD0_RESET |
			     MRDCKD1_RESET);

	mclk_pwrmgt_cntl &= ~(MRDCKA0_PDNB |
			      MRDCKA1_PDNB |
			      MRDCKB0_PDNB |
			      MRDCKB1_PDNB |
			      MRDCKC0_PDNB |
			      MRDCKC1_PDNB |
			      MRDCKD0_PDNB |
			      MRDCKD1_PDNB);

	dll_cntl |= (MRDCKA0_BYPASS |
		     MRDCKA1_BYPASS |
		     MRDCKB0_BYPASS |
		     MRDCKB1_BYPASS |
		     MRDCKC0_BYPASS |
		     MRDCKC1_BYPASS |
		     MRDCKD0_BYPASS |
		     MRDCKD1_BYPASS);

	/* evergreen only */
	if (rdev->family <= CHIP_HEMLOCK)
		spll_func_cntl |= SPLL_RESET | SPLL_SLEEP | SPLL_BYPASS_EN;

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(mpll_ad_func_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL_2 =
		cpu_to_be32(mpll_ad_func_cntl_2);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(mpll_dq_func_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL_2 =
		cpu_to_be32(mpll_dq_func_cntl_2);
	table->ACPIState.levels[0].mclk.mclk770.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);

	table->ACPIState.levels[0].mclk.mclk770.mclk_value = 0;

	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(spll_func_cntl);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(spll_func_cntl_3);

	table->ACPIState.levels[0].sclk.sclk_value = 0;

	cypress_populate_mvdd_value(rdev, 0, &table->ACPIState.levels[0].mvdd);

	if (eg_pi->dynamic_ac_timing)
		table->ACPIState.levels[0].ACIndex = 1;

	table->ACPIState.levels[1] = table->ACPIState.levels[0];
	table->ACPIState.levels[2] = table->ACPIState.levels[0];

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rv7xx_power_info {scalar_t__ mem_gddr5; scalar_t__ min_vddc_in_table; scalar_t__ acpi_pcie_gen2; scalar_t__ pcie_gen2; scalar_t__ acpi_vddc; } ;
struct radeon_device {int dummy; } ;
struct TYPE_14__ {int mpll_ad_func_cntl; int mpll_ad_func_cntl_2; int mpll_dq_func_cntl; int mpll_dq_func_cntl_2; int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; int cg_spll_func_cntl_4; int mclk_pwrmgt_cntl; int dll_cntl; } ;
struct ni_power_info {TYPE_4__ clock_registers; } ;
struct evergreen_power_info {scalar_t__ dynamic_ac_timing; scalar_t__ acpi_vddci; int /*<<< orphan*/  vddci_voltage_table; scalar_t__ vddci_control; int /*<<< orphan*/  vddc_voltage_table; } ;
struct TYPE_18__ {int /*<<< orphan*/  index; } ;
struct TYPE_15__ {TYPE_6__* levels; int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {TYPE_5__ ACPIState; TYPE_5__ initialState; } ;
struct TYPE_13__ {scalar_t__ BelowSafeInc; scalar_t__ AboveSafeInc; scalar_t__ NearTDPDec; scalar_t__ MaxPS; } ;
struct TYPE_12__ {scalar_t__ sclk_value; void* vCG_SPLL_FUNC_CNTL_4; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct TYPE_11__ {scalar_t__ mclk_value; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_DQ_FUNC_CNTL_2; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL_2; void* vMPLL_AD_FUNC_CNTL; } ;
struct TYPE_16__ {int gen2PCIE; int ACIndex; void* SQPowerThrottle_2; void* SQPowerThrottle; TYPE_3__ dpm2; int /*<<< orphan*/  mvdd; TYPE_2__ sclk; TYPE_1__ mclk; TYPE_8__ vddci; int /*<<< orphan*/  std_vddc; TYPE_8__ vddc; } ;
typedef  TYPE_7__ NISLANDS_SMC_STATETABLE ;

/* Variables and functions */
 int BIAS_GEN_PDNB ; 
 int BYPASS ; 
 int LTI_RATIO_MASK ; 
 int MAX_POWER_DELTA_MASK ; 
 int MAX_POWER_MASK ; 
 int MIN_POWER_MASK ; 
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
 int STI_SIZE_MASK ; 
 void* cpu_to_be32 (int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int ni_get_std_voltage_value (struct radeon_device*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ni_populate_mvdd_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ni_populate_std_voltage_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ni_populate_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,scalar_t__,TYPE_8__*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ni_populate_smc_acpi_state(struct radeon_device *rdev,
				      NISLANDS_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	u32 mpll_ad_func_cntl   = ni_pi->clock_registers.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 = ni_pi->clock_registers.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl   = ni_pi->clock_registers.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 = ni_pi->clock_registers.mpll_dq_func_cntl_2;
	u32 spll_func_cntl      = ni_pi->clock_registers.cg_spll_func_cntl;
	u32 spll_func_cntl_2    = ni_pi->clock_registers.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3    = ni_pi->clock_registers.cg_spll_func_cntl_3;
	u32 spll_func_cntl_4    = ni_pi->clock_registers.cg_spll_func_cntl_4;
	u32 mclk_pwrmgt_cntl    = ni_pi->clock_registers.mclk_pwrmgt_cntl;
	u32 dll_cntl            = ni_pi->clock_registers.dll_cntl;
	u32 reg;
	int ret;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	if (pi->acpi_vddc) {
		ret = ni_populate_voltage_value(rdev,
						&eg_pi->vddc_voltage_table,
						pi->acpi_vddc, &table->ACPIState.levels[0].vddc);
		if (!ret) {
			u16 std_vddc;

			ret = ni_get_std_voltage_value(rdev,
						       &table->ACPIState.levels[0].vddc, &std_vddc);
			if (!ret)
				ni_populate_std_voltage_value(rdev, std_vddc,
							      table->ACPIState.levels[0].vddc.index,
							      &table->ACPIState.levels[0].std_vddc);
		}

		if (pi->pcie_gen2) {
			if (pi->acpi_pcie_gen2)
				table->ACPIState.levels[0].gen2PCIE = 1;
			else
				table->ACPIState.levels[0].gen2PCIE = 0;
		} else {
			table->ACPIState.levels[0].gen2PCIE = 0;
		}
	} else {
		ret = ni_populate_voltage_value(rdev,
						&eg_pi->vddc_voltage_table,
						pi->min_vddc_in_table,
						&table->ACPIState.levels[0].vddc);
		if (!ret) {
			u16 std_vddc;

			ret = ni_get_std_voltage_value(rdev,
						       &table->ACPIState.levels[0].vddc,
						       &std_vddc);
			if (!ret)
				ni_populate_std_voltage_value(rdev, std_vddc,
							      table->ACPIState.levels[0].vddc.index,
							      &table->ACPIState.levels[0].std_vddc);
		}
		table->ACPIState.levels[0].gen2PCIE = 0;
	}

	if (eg_pi->acpi_vddci) {
		if (eg_pi->vddci_control)
			ni_populate_voltage_value(rdev,
						  &eg_pi->vddci_voltage_table,
						  eg_pi->acpi_vddci,
						  &table->ACPIState.levels[0].vddci);
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

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.levels[0].mclk.vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	table->ACPIState.levels[0].mclk.vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	table->ACPIState.levels[0].mclk.vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	table->ACPIState.levels[0].mclk.vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);
	table->ACPIState.levels[0].mclk.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.levels[0].mclk.vDLL_CNTL = cpu_to_be32(dll_cntl);

	table->ACPIState.levels[0].mclk.mclk_value = 0;

	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL = cpu_to_be32(spll_func_cntl);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(spll_func_cntl_3);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_4 = cpu_to_be32(spll_func_cntl_4);

	table->ACPIState.levels[0].sclk.sclk_value = 0;

	ni_populate_mvdd_value(rdev, 0, &table->ACPIState.levels[0].mvdd);

	if (eg_pi->dynamic_ac_timing)
		table->ACPIState.levels[0].ACIndex = 1;

	table->ACPIState.levels[0].dpm2.MaxPS = 0;
	table->ACPIState.levels[0].dpm2.NearTDPDec = 0;
	table->ACPIState.levels[0].dpm2.AboveSafeInc = 0;
	table->ACPIState.levels[0].dpm2.BelowSafeInc = 0;

	reg = MIN_POWER_MASK | MAX_POWER_MASK;
	table->ACPIState.levels[0].SQPowerThrottle = cpu_to_be32(reg);

	reg = MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
	table->ACPIState.levels[0].SQPowerThrottle_2 = cpu_to_be32(reg);

	return 0;
}
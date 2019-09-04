#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_25__ {int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; int cg_spll_func_cntl_4; int dll_cntl; int mclk_pwrmgt_cntl; int mpll_ad_func_cntl; int mpll_dq_func_cntl; int mpll_func_cntl; int mpll_func_cntl_1; int mpll_func_cntl_2; int mpll_ss1; int mpll_ss2; } ;
struct si_power_info {TYPE_9__ clock_registers; scalar_t__ vddc_phase_shed_control; int /*<<< orphan*/  boot_pcie_gen; int /*<<< orphan*/  sys_pcie_mask; int /*<<< orphan*/  acpi_pcie_gen; } ;
struct rv7xx_power_info {scalar_t__ acpi_vddc; scalar_t__ min_vddc_in_table; } ;
struct evergreen_power_info {scalar_t__ dynamic_ac_timing; scalar_t__ acpi_vddci; int /*<<< orphan*/  vddci_voltage_table; int /*<<< orphan*/  vddc_voltage_table; } ;
struct TYPE_17__ {int /*<<< orphan*/  phase_shedding_limits_table; } ;
struct TYPE_18__ {TYPE_1__ dyn_state; } ;
struct TYPE_19__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct TYPE_24__ {TYPE_7__* levels; int /*<<< orphan*/  flags; } ;
struct TYPE_22__ {scalar_t__ PwrEfficiencyRatio; scalar_t__ BelowSafeInc; scalar_t__ AboveSafeInc; scalar_t__ NearTDPDec; scalar_t__ MaxPS; } ;
struct TYPE_21__ {scalar_t__ sclk_value; void* vCG_SPLL_FUNC_CNTL_4; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct TYPE_20__ {scalar_t__ mclk_value; void* vMPLL_SS2; void* vMPLL_SS; void* vMPLL_FUNC_CNTL_2; void* vMPLL_FUNC_CNTL_1; void* vMPLL_FUNC_CNTL; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL; void* vMCLK_PWRMGT_CNTL; void* vDLL_CNTL; } ;
struct TYPE_16__ {int /*<<< orphan*/  index; } ;
struct TYPE_23__ {void* SQPowerThrottle_2; void* SQPowerThrottle; TYPE_6__ dpm2; scalar_t__ ACIndex; int /*<<< orphan*/  mvdd; TYPE_5__ sclk; TYPE_4__ mclk; TYPE_11__ vddci; TYPE_11__ vddc; int /*<<< orphan*/  gen2PCIE; int /*<<< orphan*/  std_vddc; } ;
struct TYPE_15__ {TYPE_8__ ACPIState; TYPE_8__ initialState; } ;
typedef  TYPE_10__ SISLANDS_SMC_STATETABLE ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PCIE_GEN1 ; 
 int LTI_RATIO_MASK ; 
 int MAX_POWER_DELTA_MASK ; 
 int MAX_POWER_MASK ; 
 int MIN_POWER_MASK ; 
 int MRDCK0_BYPASS ; 
 int MRDCK0_PDNB ; 
 int MRDCK0_RESET ; 
 int MRDCK1_BYPASS ; 
 int MRDCK1_PDNB ; 
 int MRDCK1_RESET ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int SCLK_MUX_SEL (int) ; 
 int SCLK_MUX_SEL_MASK ; 
 int STI_SIZE_MASK ; 
 scalar_t__ amdgpu_get_pcie_gen_support (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int si_get_std_voltage_value (struct amdgpu_device*,TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_populate_mvdd_value (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_populate_phase_shedding_value (struct amdgpu_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  si_populate_std_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si_populate_voltage_value (struct amdgpu_device*,int /*<<< orphan*/ *,scalar_t__,TYPE_11__*) ; 

__attribute__((used)) static int si_populate_smc_acpi_state(struct amdgpu_device *adev,
				      SISLANDS_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);
	u32 spll_func_cntl = si_pi->clock_registers.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = si_pi->clock_registers.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 = si_pi->clock_registers.cg_spll_func_cntl_3;
	u32 spll_func_cntl_4 = si_pi->clock_registers.cg_spll_func_cntl_4;
	u32 dll_cntl = si_pi->clock_registers.dll_cntl;
	u32 mclk_pwrmgt_cntl = si_pi->clock_registers.mclk_pwrmgt_cntl;
	u32 mpll_ad_func_cntl = si_pi->clock_registers.mpll_ad_func_cntl;
	u32 mpll_dq_func_cntl = si_pi->clock_registers.mpll_dq_func_cntl;
	u32 mpll_func_cntl = si_pi->clock_registers.mpll_func_cntl;
	u32 mpll_func_cntl_1 = si_pi->clock_registers.mpll_func_cntl_1;
	u32 mpll_func_cntl_2 = si_pi->clock_registers.mpll_func_cntl_2;
	u32 reg;
	int ret;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	if (pi->acpi_vddc) {
		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						pi->acpi_vddc, &table->ACPIState.levels[0].vddc);
		if (!ret) {
			u16 std_vddc;

			ret = si_get_std_voltage_value(adev,
						       &table->ACPIState.levels[0].vddc, &std_vddc);
			if (!ret)
				si_populate_std_voltage_value(adev, std_vddc,
							      table->ACPIState.levels[0].vddc.index,
							      &table->ACPIState.levels[0].std_vddc);
		}
		table->ACPIState.levels[0].gen2PCIE = si_pi->acpi_pcie_gen;

		if (si_pi->vddc_phase_shed_control) {
			si_populate_phase_shedding_value(adev,
							 &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
							 pi->acpi_vddc,
							 0,
							 0,
							 &table->ACPIState.levels[0].vddc);
		}
	} else {
		ret = si_populate_voltage_value(adev, &eg_pi->vddc_voltage_table,
						pi->min_vddc_in_table, &table->ACPIState.levels[0].vddc);
		if (!ret) {
			u16 std_vddc;

			ret = si_get_std_voltage_value(adev,
						       &table->ACPIState.levels[0].vddc, &std_vddc);

			if (!ret)
				si_populate_std_voltage_value(adev, std_vddc,
							      table->ACPIState.levels[0].vddc.index,
							      &table->ACPIState.levels[0].std_vddc);
		}
		table->ACPIState.levels[0].gen2PCIE =
			(u8)amdgpu_get_pcie_gen_support(adev,
							si_pi->sys_pcie_mask,
							si_pi->boot_pcie_gen,
							AMDGPU_PCIE_GEN1);

		if (si_pi->vddc_phase_shed_control)
			si_populate_phase_shedding_value(adev,
							 &adev->pm.dpm.dyn_state.phase_shedding_limits_table,
							 pi->min_vddc_in_table,
							 0,
							 0,
							 &table->ACPIState.levels[0].vddc);
	}

	if (pi->acpi_vddc) {
		if (eg_pi->acpi_vddci)
			si_populate_voltage_value(adev, &eg_pi->vddci_voltage_table,
						  eg_pi->acpi_vddci,
						  &table->ACPIState.levels[0].vddci);
	}

	mclk_pwrmgt_cntl |= MRDCK0_RESET | MRDCK1_RESET;
	mclk_pwrmgt_cntl &= ~(MRDCK0_PDNB | MRDCK1_PDNB);

	dll_cntl &= ~(MRDCK0_BYPASS | MRDCK1_BYPASS);

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.levels[0].mclk.vDLL_CNTL =
		cpu_to_be32(dll_cntl);
	table->ACPIState.levels[0].mclk.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.levels[0].mclk.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(mpll_ad_func_cntl);
	table->ACPIState.levels[0].mclk.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(mpll_dq_func_cntl);
	table->ACPIState.levels[0].mclk.vMPLL_FUNC_CNTL =
		cpu_to_be32(mpll_func_cntl);
	table->ACPIState.levels[0].mclk.vMPLL_FUNC_CNTL_1 =
		cpu_to_be32(mpll_func_cntl_1);
	table->ACPIState.levels[0].mclk.vMPLL_FUNC_CNTL_2 =
		cpu_to_be32(mpll_func_cntl_2);
	table->ACPIState.levels[0].mclk.vMPLL_SS =
		cpu_to_be32(si_pi->clock_registers.mpll_ss1);
	table->ACPIState.levels[0].mclk.vMPLL_SS2 =
		cpu_to_be32(si_pi->clock_registers.mpll_ss2);

	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(spll_func_cntl);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(spll_func_cntl_3);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_4 =
		cpu_to_be32(spll_func_cntl_4);

	table->ACPIState.levels[0].mclk.mclk_value = 0;
	table->ACPIState.levels[0].sclk.sclk_value = 0;

	si_populate_mvdd_value(adev, 0, &table->ACPIState.levels[0].mvdd);

	if (eg_pi->dynamic_ac_timing)
		table->ACPIState.levels[0].ACIndex = 0;

	table->ACPIState.levels[0].dpm2.MaxPS = 0;
	table->ACPIState.levels[0].dpm2.NearTDPDec = 0;
	table->ACPIState.levels[0].dpm2.AboveSafeInc = 0;
	table->ACPIState.levels[0].dpm2.BelowSafeInc = 0;
	table->ACPIState.levels[0].dpm2.PwrEfficiencyRatio = 0;

	reg = MIN_POWER_MASK | MAX_POWER_MASK;
	table->ACPIState.levels[0].SQPowerThrottle = cpu_to_be32(reg);

	reg = MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
	table->ACPIState.levels[0].SQPowerThrottle_2 = cpu_to_be32(reg);

	return 0;
}
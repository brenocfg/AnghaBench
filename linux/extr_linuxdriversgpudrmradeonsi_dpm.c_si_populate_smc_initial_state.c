#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_25__ {int dll_cntl; int mclk_pwrmgt_cntl; int mpll_ad_func_cntl; int mpll_dq_func_cntl; int mpll_func_cntl; int mpll_func_cntl_1; int mpll_func_cntl_2; int mpll_ss1; int mpll_ss2; int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; int cg_spll_func_cntl_4; int cg_spll_spread_spectrum; int cg_spll_spread_spectrum_2; } ;
struct si_power_info {scalar_t__ boot_pcie_gen; scalar_t__ vddc_phase_shed_control; TYPE_7__ clock_registers; } ;
struct rv7xx_power_info {int dsp; scalar_t__ mclk_edc_enable_threshold; scalar_t__ mem_gddr5; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  phase_shedding_limits_table; } ;
struct TYPE_21__ {TYPE_2__ dyn_state; } ;
struct TYPE_22__ {TYPE_3__ dpm; } ;
struct radeon_device {TYPE_4__ pm; } ;
struct ni_ps {TYPE_5__* performance_levels; } ;
struct evergreen_power_info {int /*<<< orphan*/  vddci_voltage_table; scalar_t__ vddci_control; int /*<<< orphan*/  vddc_voltage_table; } ;
struct TYPE_27__ {int levelCount; TYPE_10__* levels; int /*<<< orphan*/  flags; } ;
struct TYPE_26__ {void* mclk_value; void* vMPLL_SS2; void* vMPLL_SS; void* vMPLL_FUNC_CNTL_2; void* vMPLL_FUNC_CNTL_1; void* vMPLL_FUNC_CNTL; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL; void* vMCLK_PWRMGT_CNTL; void* vDLL_CNTL; } ;
struct TYPE_24__ {scalar_t__ PwrEfficiencyRatio; scalar_t__ BelowSafeInc; scalar_t__ AboveSafeInc; scalar_t__ NearTDPDec; scalar_t__ MaxPS; } ;
struct TYPE_23__ {int mclk; int sclk; int /*<<< orphan*/  vddc; int /*<<< orphan*/  vddci; } ;
struct TYPE_19__ {void* sclk_value; void* vCG_SPLL_SPREAD_SPECTRUM_2; void* vCG_SPLL_SPREAD_SPECTRUM; void* vCG_SPLL_FUNC_CNTL_4; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct TYPE_18__ {int /*<<< orphan*/  index; } ;
struct TYPE_17__ {TYPE_9__ initialState; } ;
struct TYPE_16__ {int mcFlags; void* SQPowerThrottle_2; void* SQPowerThrottle; TYPE_6__ dpm2; int /*<<< orphan*/  strobeMode; scalar_t__ gen2PCIE; void* bSP; void* aT; int /*<<< orphan*/  mvdd; TYPE_12__ vddc; TYPE_12__ vddci; int /*<<< orphan*/  std_vddc; scalar_t__ ACIndex; int /*<<< orphan*/  arbRefreshState; TYPE_1__ sclk; TYPE_8__ mclk; } ;
typedef  TYPE_11__ SISLANDS_SMC_STATETABLE ;

/* Variables and functions */
 int CG_L (int /*<<< orphan*/ ) ; 
 int CG_R (int) ; 
 int LTI_RATIO_MASK ; 
 int MAX_POWER_DELTA_MASK ; 
 int MAX_POWER_MASK ; 
 int MIN_POWER_MASK ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int /*<<< orphan*/  SISLANDS_INITIAL_STATE_ARB_INDEX ; 
 int SISLANDS_SMC_MC_EDC_RD_FLAG ; 
 int SISLANDS_SMC_MC_EDC_WR_FLAG ; 
 int STI_SIZE_MASK ; 
 void* cpu_to_be32 (int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_get_std_voltage_value (struct radeon_device*,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_get_strobe_mode_settings (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_populate_initial_mvdd_value (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_populate_phase_shedding_value (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,TYPE_12__*) ; 
 int /*<<< orphan*/  si_populate_std_voltage_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si_populate_voltage_value (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_12__*) ; 

__attribute__((used)) static int si_populate_smc_initial_state(struct radeon_device *rdev,
					 struct radeon_ps *radeon_initial_state,
					 SISLANDS_SMC_STATETABLE *table)
{
	struct ni_ps *initial_state = ni_get_ps(radeon_initial_state);
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	u32 reg;
	int ret;

	table->initialState.levels[0].mclk.vDLL_CNTL =
		cpu_to_be32(si_pi->clock_registers.dll_cntl);
	table->initialState.levels[0].mclk.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(si_pi->clock_registers.mclk_pwrmgt_cntl);
	table->initialState.levels[0].mclk.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(si_pi->clock_registers.mpll_ad_func_cntl);
	table->initialState.levels[0].mclk.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(si_pi->clock_registers.mpll_dq_func_cntl);
	table->initialState.levels[0].mclk.vMPLL_FUNC_CNTL =
		cpu_to_be32(si_pi->clock_registers.mpll_func_cntl);
	table->initialState.levels[0].mclk.vMPLL_FUNC_CNTL_1 =
		cpu_to_be32(si_pi->clock_registers.mpll_func_cntl_1);
	table->initialState.levels[0].mclk.vMPLL_FUNC_CNTL_2 =
		cpu_to_be32(si_pi->clock_registers.mpll_func_cntl_2);
	table->initialState.levels[0].mclk.vMPLL_SS =
		cpu_to_be32(si_pi->clock_registers.mpll_ss1);
	table->initialState.levels[0].mclk.vMPLL_SS2 =
		cpu_to_be32(si_pi->clock_registers.mpll_ss2);

	table->initialState.levels[0].mclk.mclk_value =
		cpu_to_be32(initial_state->performance_levels[0].mclk);

	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(si_pi->clock_registers.cg_spll_func_cntl);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(si_pi->clock_registers.cg_spll_func_cntl_2);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(si_pi->clock_registers.cg_spll_func_cntl_3);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_4 =
		cpu_to_be32(si_pi->clock_registers.cg_spll_func_cntl_4);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM =
		cpu_to_be32(si_pi->clock_registers.cg_spll_spread_spectrum);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM_2  =
		cpu_to_be32(si_pi->clock_registers.cg_spll_spread_spectrum_2);

	table->initialState.levels[0].sclk.sclk_value =
		cpu_to_be32(initial_state->performance_levels[0].sclk);

	table->initialState.levels[0].arbRefreshState =
		SISLANDS_INITIAL_STATE_ARB_INDEX;

	table->initialState.levels[0].ACIndex = 0;

	ret = si_populate_voltage_value(rdev, &eg_pi->vddc_voltage_table,
					initial_state->performance_levels[0].vddc,
					&table->initialState.levels[0].vddc);

	if (!ret) {
		u16 std_vddc;

		ret = si_get_std_voltage_value(rdev,
					       &table->initialState.levels[0].vddc,
					       &std_vddc);
		if (!ret)
			si_populate_std_voltage_value(rdev, std_vddc,
						      table->initialState.levels[0].vddc.index,
						      &table->initialState.levels[0].std_vddc);
	}

	if (eg_pi->vddci_control)
		si_populate_voltage_value(rdev,
					  &eg_pi->vddci_voltage_table,
					  initial_state->performance_levels[0].vddci,
					  &table->initialState.levels[0].vddci);

	if (si_pi->vddc_phase_shed_control)
		si_populate_phase_shedding_value(rdev,
						 &rdev->pm.dpm.dyn_state.phase_shedding_limits_table,
						 initial_state->performance_levels[0].vddc,
						 initial_state->performance_levels[0].sclk,
						 initial_state->performance_levels[0].mclk,
						 &table->initialState.levels[0].vddc);

	si_populate_initial_mvdd_value(rdev, &table->initialState.levels[0].mvdd);

	reg = CG_R(0xffff) | CG_L(0);
	table->initialState.levels[0].aT = cpu_to_be32(reg);

	table->initialState.levels[0].bSP = cpu_to_be32(pi->dsp);

	table->initialState.levels[0].gen2PCIE = (u8)si_pi->boot_pcie_gen;

	if (pi->mem_gddr5) {
		table->initialState.levels[0].strobeMode =
			si_get_strobe_mode_settings(rdev,
						    initial_state->performance_levels[0].mclk);

		if (initial_state->performance_levels[0].mclk > pi->mclk_edc_enable_threshold)
			table->initialState.levels[0].mcFlags = SISLANDS_SMC_MC_EDC_RD_FLAG | SISLANDS_SMC_MC_EDC_WR_FLAG;
		else
			table->initialState.levels[0].mcFlags =  0;
	}

	table->initialState.levelCount = 1;

	table->initialState.flags |= PPSMC_SWSTATE_FLAG_DC;

	table->initialState.levels[0].dpm2.MaxPS = 0;
	table->initialState.levels[0].dpm2.NearTDPDec = 0;
	table->initialState.levels[0].dpm2.AboveSafeInc = 0;
	table->initialState.levels[0].dpm2.BelowSafeInc = 0;
	table->initialState.levels[0].dpm2.PwrEfficiencyRatio = 0;

	reg = MIN_POWER_MASK | MAX_POWER_MASK;
	table->initialState.levels[0].SQPowerThrottle = cpu_to_be32(reg);

	reg = MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
	table->initialState.levels[0].SQPowerThrottle_2 = cpu_to_be32(reg);

	return 0;
}
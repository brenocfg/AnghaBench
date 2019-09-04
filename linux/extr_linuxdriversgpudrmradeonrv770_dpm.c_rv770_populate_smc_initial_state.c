#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int mclk; int sclk; int flags; int /*<<< orphan*/  vddc; } ;
struct rv7xx_ps {TYPE_10__ low; } ;
struct TYPE_15__ {int mpll_ad_func_cntl; int mpll_ad_func_cntl_2; int mpll_dq_func_cntl; int mpll_dq_func_cntl_2; int mclk_pwrmgt_cntl; int dll_cntl; int mpll_ss1; int mpll_ss2; int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; int cg_spll_spread_spectrum; int cg_spll_spread_spectrum_2; } ;
struct TYPE_16__ {TYPE_4__ rv770; } ;
struct rv7xx_power_info {int dsp; scalar_t__ mclk_strobe_mode_threshold; scalar_t__ mclk_edc_enable_threshold; scalar_t__ mem_gddr5; scalar_t__ boot_in_gen2; TYPE_5__ clk_regs; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {scalar_t__ family; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; TYPE_7__* levels; } ;
struct TYPE_19__ {TYPE_3__ initialState; } ;
struct TYPE_17__ {void* sclk_value; void* vCG_SPLL_SPREAD_SPECTRUM_2; void* vCG_SPLL_SPREAD_SPECTRUM; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct TYPE_12__ {void* mclk_value; void* vMPLL_SS2; void* vMPLL_SS; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_DQ_FUNC_CNTL_2; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL_2; void* vMPLL_AD_FUNC_CNTL; } ;
struct TYPE_13__ {TYPE_1__ mclk770; } ;
struct TYPE_18__ {int gen2PCIE; int gen2XSP; int strobeMode; int mcFlags; void* bSP; void* aT; int /*<<< orphan*/  mvdd; int /*<<< orphan*/  vddc; int /*<<< orphan*/  seqValue; int /*<<< orphan*/  arbValue; TYPE_6__ sclk; TYPE_2__ mclk; } ;
typedef  TYPE_8__ RV770_SMC_STATETABLE ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 int CG_L (int /*<<< orphan*/ ) ; 
 int CG_R (int) ; 
 scalar_t__ CHIP_RV740 ; 
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F0 ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int SMC_MC_EDC_RD_FLAG ; 
 int SMC_MC_EDC_WR_FLAG ; 
 void* cpu_to_be32 (int) ; 
 int rv740_get_mclk_frequency_ratio (scalar_t__) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  rv770_get_seq_value (struct radeon_device*,TYPE_10__*) ; 
 int /*<<< orphan*/  rv770_populate_initial_mvdd_value (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rv770_populate_vddc_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rv770_populate_smc_initial_state(struct radeon_device *rdev,
					    struct radeon_ps *radeon_state,
					    RV770_SMC_STATETABLE *table)
{
	struct rv7xx_ps *initial_state = rv770_get_ps(radeon_state);
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 a_t;

	table->initialState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ad_func_cntl);
	table->initialState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ad_func_cntl_2);
	table->initialState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mpll_dq_func_cntl);
	table->initialState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_dq_func_cntl_2);
	table->initialState.levels[0].mclk.mclk770.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mclk_pwrmgt_cntl);
	table->initialState.levels[0].mclk.mclk770.vDLL_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.dll_cntl);

	table->initialState.levels[0].mclk.mclk770.vMPLL_SS =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ss1);
	table->initialState.levels[0].mclk.mclk770.vMPLL_SS2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ss2);

	table->initialState.levels[0].mclk.mclk770.mclk_value =
		cpu_to_be32(initial_state->low.mclk);

	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl_2);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl_3);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_spread_spectrum);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM_2 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_spread_spectrum_2);

	table->initialState.levels[0].sclk.sclk_value =
		cpu_to_be32(initial_state->low.sclk);

	table->initialState.levels[0].arbValue = MC_CG_ARB_FREQ_F0;

	table->initialState.levels[0].seqValue =
		rv770_get_seq_value(rdev, &initial_state->low);

	rv770_populate_vddc_value(rdev,
				  initial_state->low.vddc,
				  &table->initialState.levels[0].vddc);
	rv770_populate_initial_mvdd_value(rdev,
					  &table->initialState.levels[0].mvdd);

	a_t = CG_R(0xffff) | CG_L(0);
	table->initialState.levels[0].aT = cpu_to_be32(a_t);

	table->initialState.levels[0].bSP = cpu_to_be32(pi->dsp);

	if (pi->boot_in_gen2)
		table->initialState.levels[0].gen2PCIE = 1;
	else
		table->initialState.levels[0].gen2PCIE = 0;
	if (initial_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
		table->initialState.levels[0].gen2XSP = 1;
	else
		table->initialState.levels[0].gen2XSP = 0;

	if (rdev->family == CHIP_RV740) {
		if (pi->mem_gddr5) {
			if (initial_state->low.mclk <= pi->mclk_strobe_mode_threshold)
				table->initialState.levels[0].strobeMode =
					rv740_get_mclk_frequency_ratio(initial_state->low.mclk) | 0x10;
			else
				table->initialState.levels[0].strobeMode = 0;

			if (initial_state->low.mclk >= pi->mclk_edc_enable_threshold)
				table->initialState.levels[0].mcFlags = SMC_MC_EDC_RD_FLAG | SMC_MC_EDC_WR_FLAG;
			else
				table->initialState.levels[0].mcFlags =  0;
		}
	}

	table->initialState.levels[1] = table->initialState.levels[0];
	table->initialState.levels[2] = table->initialState.levels[0];

	table->initialState.flags |= PPSMC_SWSTATE_FLAG_DC;

	return 0;
}
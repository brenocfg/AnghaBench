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
struct TYPE_10__ {int mpll_func_cntl; int mpll_func_cntl2; int mpll_func_cntl3; int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; } ;
struct TYPE_11__ {TYPE_1__ rv730; } ;
struct rv7xx_power_info {TYPE_2__ clk_regs; scalar_t__ min_vddc_in_table; int /*<<< orphan*/  acpi_pcie_gen2; scalar_t__ pcie_gen2; scalar_t__ acpi_vddc; } ;
struct radeon_device {int dummy; } ;
struct TYPE_15__ {TYPE_7__* levels; int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {TYPE_6__ ACPIState; TYPE_6__ initialState; } ;
struct TYPE_14__ {scalar_t__ sclk_value; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct TYPE_12__ {scalar_t__ mclk_value; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_FUNC_CNTL3; void* vMPLL_FUNC_CNTL2; void* vMPLL_FUNC_CNTL; } ;
struct TYPE_13__ {TYPE_3__ mclk730; } ;
struct TYPE_16__ {int /*<<< orphan*/  mvdd; TYPE_5__ sclk; TYPE_4__ mclk; int /*<<< orphan*/  gen2PCIE; int /*<<< orphan*/  vddc; int /*<<< orphan*/  gen2XSP; } ;
typedef  TYPE_8__ RV770_SMC_STATETABLE ;

/* Variables and functions */
 int MCLK_MUX_SEL (int) ; 
 int MCLK_MUX_SEL_MASK ; 
 int MPLL_BYPASS_EN ; 
 int MPLL_RESET ; 
 int MPLL_SLEEP ; 
 int MRDCKA_RESET ; 
 int MRDCKA_SLEEP ; 
 int MRDCKB_RESET ; 
 int MRDCKB_SLEEP ; 
 int MRDCKC_RESET ; 
 int MRDCKC_SLEEP ; 
 int MRDCKD_RESET ; 
 int MRDCKD_SLEEP ; 
 int MRDCKE_RESET ; 
 int MRDCKE_SLEEP ; 
 int MRDCKF_RESET ; 
 int MRDCKF_SLEEP ; 
 int MRDCKG_RESET ; 
 int MRDCKG_SLEEP ; 
 int MRDCKH_RESET ; 
 int MRDCKH_SLEEP ; 
 int /*<<< orphan*/  PPSMC_SWSTATE_FLAG_DC ; 
 int SCLK_MUX_SEL (int) ; 
 int SCLK_MUX_SEL_MASK ; 
 int SPLL_BYPASS_EN ; 
 int SPLL_RESET ; 
 int SPLL_SLEEP ; 
 void* cpu_to_be32 (int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_populate_mvdd_value (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rv770_populate_vddc_value (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *) ; 

int rv730_populate_smc_acpi_state(struct radeon_device *rdev,
				  RV770_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 mpll_func_cntl = 0;
	u32 mpll_func_cntl_2 = 0 ;
	u32 mpll_func_cntl_3 = 0;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 spll_func_cntl;
	u32 spll_func_cntl_2;
	u32 spll_func_cntl_3;

	table->ACPIState = table->initialState;
	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	if (pi->acpi_vddc) {
		rv770_populate_vddc_value(rdev, pi->acpi_vddc,
					  &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE = pi->pcie_gen2 ?
			pi->acpi_pcie_gen2 : 0;
		table->ACPIState.levels[0].gen2XSP =
			pi->acpi_pcie_gen2;
	} else {
		rv770_populate_vddc_value(rdev, pi->min_vddc_in_table,
					  &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE = 0;
	}

	mpll_func_cntl = pi->clk_regs.rv730.mpll_func_cntl;
	mpll_func_cntl_2 = pi->clk_regs.rv730.mpll_func_cntl2;
	mpll_func_cntl_3 = pi->clk_regs.rv730.mpll_func_cntl3;

	mpll_func_cntl |= MPLL_RESET | MPLL_BYPASS_EN;
	mpll_func_cntl &= ~MPLL_SLEEP;

	mpll_func_cntl_2 &= ~MCLK_MUX_SEL_MASK;
	mpll_func_cntl_2 |= MCLK_MUX_SEL(1);

	mclk_pwrmgt_cntl = (MRDCKA_RESET |
			    MRDCKB_RESET |
			    MRDCKC_RESET |
			    MRDCKD_RESET |
			    MRDCKE_RESET |
			    MRDCKF_RESET |
			    MRDCKG_RESET |
			    MRDCKH_RESET |
			    MRDCKA_SLEEP |
			    MRDCKB_SLEEP |
			    MRDCKC_SLEEP |
			    MRDCKD_SLEEP |
			    MRDCKE_SLEEP |
			    MRDCKF_SLEEP |
			    MRDCKG_SLEEP |
			    MRDCKH_SLEEP);

	dll_cntl = 0xff000000;

	spll_func_cntl = pi->clk_regs.rv730.cg_spll_func_cntl;
	spll_func_cntl_2 = pi->clk_regs.rv730.cg_spll_func_cntl_2;
	spll_func_cntl_3 = pi->clk_regs.rv730.cg_spll_func_cntl_3;

	spll_func_cntl |= SPLL_RESET | SPLL_BYPASS_EN;
	spll_func_cntl &= ~SPLL_SLEEP;

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.levels[0].mclk.mclk730.vMPLL_FUNC_CNTL = cpu_to_be32(mpll_func_cntl);
	table->ACPIState.levels[0].mclk.mclk730.vMPLL_FUNC_CNTL2 = cpu_to_be32(mpll_func_cntl_2);
	table->ACPIState.levels[0].mclk.mclk730.vMPLL_FUNC_CNTL3 = cpu_to_be32(mpll_func_cntl_3);
	table->ACPIState.levels[0].mclk.mclk730.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.levels[0].mclk.mclk730.vDLL_CNTL = cpu_to_be32(dll_cntl);

	table->ACPIState.levels[0].mclk.mclk730.mclk_value = 0;

	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL = cpu_to_be32(spll_func_cntl);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(spll_func_cntl_3);

	table->ACPIState.levels[0].sclk.sclk_value = 0;

	rv770_populate_mvdd_value(rdev, 0, &table->ACPIState.levels[0].mvdd);

	table->ACPIState.levels[1] = table->ACPIState.levels[0];
	table->ACPIState.levels[2] = table->ACPIState.levels[0];

	return 0;
}
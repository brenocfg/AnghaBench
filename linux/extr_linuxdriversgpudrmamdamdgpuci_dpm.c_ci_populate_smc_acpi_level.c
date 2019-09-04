#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_13__ {int cg_spll_func_cntl; int cg_spll_func_cntl_2; int dll_cntl; int mclk_pwrmgt_cntl; int cg_spll_func_cntl_3; int cg_spll_func_cntl_4; int cg_spll_spread_spectrum; int cg_spll_spread_spectrum_2; int mpll_ad_func_cntl; int mpll_dq_func_cntl; int mpll_func_cntl; int mpll_func_cntl_1; int mpll_func_cntl_2; int mpll_ss1; int mpll_ss2; } ;
struct ci_power_info {int acpi_vddc; int min_vddc_in_pp_table; scalar_t__ vddci_control; int acpi_vddci; int min_vddci_in_pp_table; scalar_t__ mclk_activity_target; TYPE_4__ clock_registers; scalar_t__ vddc_phase_shed_control; } ;
struct atom_clock_dividers {scalar_t__ post_divider; } ;
struct TYPE_11__ {int reference_freq; } ;
struct TYPE_12__ {TYPE_2__ spll; } ;
struct amdgpu_device {TYPE_3__ clock; } ;
struct TYPE_10__ {int MinVddcPhases; int DownH; int StutterEnable; int StrobeEnable; int EdcReadEnable; int EdcWriteEnable; int RttEnable; int /*<<< orphan*/  ActivityLevel; scalar_t__ VoltageDownH; scalar_t__ UpH; scalar_t__ EnabledForActivity; scalar_t__ EnabledForThrottle; void* MpllSs2; void* MpllSs1; void* MpllFuncCntl_2; void* MpllFuncCntl_1; void* MpllFuncCntl; void* MpllDqFuncCntl; void* MpllAdFuncCntl; void* MclkPwrmgtCntl; void* DllCntl; void* MinMvdd; void* MinVddci; void* MinVddc; } ;
struct TYPE_14__ {int Flags; int MinVddcPhases; int SclkFrequency; int CgSpllFuncCntl; int CgSpllFuncCntl2; int CgSpllFuncCntl3; int CgSpllFuncCntl4; int SpllSpreadSpectrum; int SpllSpreadSpectrum2; int CcPwrDynRm; int CcPwrDynRm1; void* MinVddc; scalar_t__ DeepSleepDivId; int /*<<< orphan*/  DisplayWatermark; scalar_t__ SclkDid; } ;
struct TYPE_16__ {TYPE_1__ MemoryACPILevel; TYPE_5__ ACPILevel; } ;
struct TYPE_15__ {int Voltage; } ;
typedef  TYPE_6__ SMU7_Discrete_VoltageLevel ;
typedef  TYPE_7__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int CG_SPLL_FUNC_CNTL_2__SCLK_MUX_SEL_MASK ; 
 int CG_SPLL_FUNC_CNTL_2__SCLK_MUX_SEL__SHIFT ; 
 int CG_SPLL_FUNC_CNTL__SPLL_PWRON_MASK ; 
 int CG_SPLL_FUNC_CNTL__SPLL_RESET_MASK ; 
 scalar_t__ CISLANDS_VOLTAGE_CONTROL_NONE ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_SCLK ; 
 int DLL_CNTL__MRDCK0_BYPASS_MASK ; 
 int DLL_CNTL__MRDCK1_BYPASS_MASK ; 
 int MCLK_PWRMGT_CNTL__MRDCK0_PDNB_MASK ; 
 int MCLK_PWRMGT_CNTL__MRDCK0_RESET_MASK ; 
 int MCLK_PWRMGT_CNTL__MRDCK1_PDNB_MASK ; 
 int MCLK_PWRMGT_CNTL__MRDCK1_RESET_MASK ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_LOW ; 
 int PPSMC_SWSTATE_FLAG_DC ; 
 int VOLTAGE_SCALE ; 
 int amdgpu_atombios_get_clock_dividers (struct amdgpu_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 scalar_t__ ci_populate_mvdd_value (struct amdgpu_device*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static int ci_populate_smc_acpi_level(struct amdgpu_device *adev,
				      SMU7_Discrete_DpmTable *table)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	struct atom_clock_dividers dividers;
	SMU7_Discrete_VoltageLevel voltage_level;
	u32 spll_func_cntl = pi->clock_registers.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = pi->clock_registers.cg_spll_func_cntl_2;
	u32 dll_cntl = pi->clock_registers.dll_cntl;
	u32 mclk_pwrmgt_cntl = pi->clock_registers.mclk_pwrmgt_cntl;
	int ret;

	table->ACPILevel.Flags &= ~PPSMC_SWSTATE_FLAG_DC;

	if (pi->acpi_vddc)
		table->ACPILevel.MinVddc = cpu_to_be32(pi->acpi_vddc * VOLTAGE_SCALE);
	else
		table->ACPILevel.MinVddc = cpu_to_be32(pi->min_vddc_in_pp_table * VOLTAGE_SCALE);

	table->ACPILevel.MinVddcPhases = pi->vddc_phase_shed_control ? 0 : 1;

	table->ACPILevel.SclkFrequency = adev->clock.spll.reference_freq;

	ret = amdgpu_atombios_get_clock_dividers(adev,
						 COMPUTE_GPUCLK_INPUT_FLAG_SCLK,
						 table->ACPILevel.SclkFrequency, false, &dividers);
	if (ret)
		return ret;

	table->ACPILevel.SclkDid = (u8)dividers.post_divider;
	table->ACPILevel.DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;
	table->ACPILevel.DeepSleepDivId = 0;

	spll_func_cntl &= ~CG_SPLL_FUNC_CNTL__SPLL_PWRON_MASK;
	spll_func_cntl |= CG_SPLL_FUNC_CNTL__SPLL_RESET_MASK;

	spll_func_cntl_2 &= ~CG_SPLL_FUNC_CNTL_2__SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= (4 << CG_SPLL_FUNC_CNTL_2__SCLK_MUX_SEL__SHIFT);

	table->ACPILevel.CgSpllFuncCntl = spll_func_cntl;
	table->ACPILevel.CgSpllFuncCntl2 = spll_func_cntl_2;
	table->ACPILevel.CgSpllFuncCntl3 = pi->clock_registers.cg_spll_func_cntl_3;
	table->ACPILevel.CgSpllFuncCntl4 = pi->clock_registers.cg_spll_func_cntl_4;
	table->ACPILevel.SpllSpreadSpectrum = pi->clock_registers.cg_spll_spread_spectrum;
	table->ACPILevel.SpllSpreadSpectrum2 = pi->clock_registers.cg_spll_spread_spectrum_2;
	table->ACPILevel.CcPwrDynRm = 0;
	table->ACPILevel.CcPwrDynRm1 = 0;

	table->ACPILevel.Flags = cpu_to_be32(table->ACPILevel.Flags);
	table->ACPILevel.MinVddcPhases = cpu_to_be32(table->ACPILevel.MinVddcPhases);
	table->ACPILevel.SclkFrequency = cpu_to_be32(table->ACPILevel.SclkFrequency);
	table->ACPILevel.CgSpllFuncCntl = cpu_to_be32(table->ACPILevel.CgSpllFuncCntl);
	table->ACPILevel.CgSpllFuncCntl2 = cpu_to_be32(table->ACPILevel.CgSpllFuncCntl2);
	table->ACPILevel.CgSpllFuncCntl3 = cpu_to_be32(table->ACPILevel.CgSpllFuncCntl3);
	table->ACPILevel.CgSpllFuncCntl4 = cpu_to_be32(table->ACPILevel.CgSpllFuncCntl4);
	table->ACPILevel.SpllSpreadSpectrum = cpu_to_be32(table->ACPILevel.SpllSpreadSpectrum);
	table->ACPILevel.SpllSpreadSpectrum2 = cpu_to_be32(table->ACPILevel.SpllSpreadSpectrum2);
	table->ACPILevel.CcPwrDynRm = cpu_to_be32(table->ACPILevel.CcPwrDynRm);
	table->ACPILevel.CcPwrDynRm1 = cpu_to_be32(table->ACPILevel.CcPwrDynRm1);

	table->MemoryACPILevel.MinVddc = table->ACPILevel.MinVddc;
	table->MemoryACPILevel.MinVddcPhases = table->ACPILevel.MinVddcPhases;

	if (pi->vddci_control != CISLANDS_VOLTAGE_CONTROL_NONE) {
		if (pi->acpi_vddci)
			table->MemoryACPILevel.MinVddci =
				cpu_to_be32(pi->acpi_vddci * VOLTAGE_SCALE);
		else
			table->MemoryACPILevel.MinVddci =
				cpu_to_be32(pi->min_vddci_in_pp_table * VOLTAGE_SCALE);
	}

	if (ci_populate_mvdd_value(adev, 0, &voltage_level))
		table->MemoryACPILevel.MinMvdd = 0;
	else
		table->MemoryACPILevel.MinMvdd =
			cpu_to_be32(voltage_level.Voltage * VOLTAGE_SCALE);

	mclk_pwrmgt_cntl |= MCLK_PWRMGT_CNTL__MRDCK0_RESET_MASK |
		MCLK_PWRMGT_CNTL__MRDCK1_RESET_MASK;
	mclk_pwrmgt_cntl &= ~(MCLK_PWRMGT_CNTL__MRDCK0_PDNB_MASK |
			MCLK_PWRMGT_CNTL__MRDCK1_PDNB_MASK);

	dll_cntl &= ~(DLL_CNTL__MRDCK0_BYPASS_MASK | DLL_CNTL__MRDCK1_BYPASS_MASK);

	table->MemoryACPILevel.DllCntl = cpu_to_be32(dll_cntl);
	table->MemoryACPILevel.MclkPwrmgtCntl = cpu_to_be32(mclk_pwrmgt_cntl);
	table->MemoryACPILevel.MpllAdFuncCntl =
		cpu_to_be32(pi->clock_registers.mpll_ad_func_cntl);
	table->MemoryACPILevel.MpllDqFuncCntl =
		cpu_to_be32(pi->clock_registers.mpll_dq_func_cntl);
	table->MemoryACPILevel.MpllFuncCntl =
		cpu_to_be32(pi->clock_registers.mpll_func_cntl);
	table->MemoryACPILevel.MpllFuncCntl_1 =
		cpu_to_be32(pi->clock_registers.mpll_func_cntl_1);
	table->MemoryACPILevel.MpllFuncCntl_2 =
		cpu_to_be32(pi->clock_registers.mpll_func_cntl_2);
	table->MemoryACPILevel.MpllSs1 = cpu_to_be32(pi->clock_registers.mpll_ss1);
	table->MemoryACPILevel.MpllSs2 = cpu_to_be32(pi->clock_registers.mpll_ss2);

	table->MemoryACPILevel.EnabledForThrottle = 0;
	table->MemoryACPILevel.EnabledForActivity = 0;
	table->MemoryACPILevel.UpH = 0;
	table->MemoryACPILevel.DownH = 100;
	table->MemoryACPILevel.VoltageDownH = 0;
	table->MemoryACPILevel.ActivityLevel =
		cpu_to_be16((u16)pi->mclk_activity_target);

	table->MemoryACPILevel.StutterEnable = false;
	table->MemoryACPILevel.StrobeEnable = false;
	table->MemoryACPILevel.EdcReadEnable = false;
	table->MemoryACPILevel.EdcWriteEnable = false;
	table->MemoryACPILevel.RttEnable = false;

	return 0;
}
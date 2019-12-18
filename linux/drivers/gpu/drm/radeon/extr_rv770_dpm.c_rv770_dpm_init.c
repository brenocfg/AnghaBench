#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rv7xx_power_info {int mclk_strobe_mode_threshold; int mclk_edc_enable_threshold; int power_gating; int gfx_clock_gating; int mg_clock_gating; int mgcgtssm; int dynamic_pcie_gen2; int thermal_protection; int display_gap; int dcodt; int ulps; int /*<<< orphan*/  soft_regs_start; int /*<<< orphan*/  state_table_start; int /*<<< orphan*/  sram_end; scalar_t__ mclk_stutter_mode_threshold; int /*<<< orphan*/  vrc; int /*<<< orphan*/  pasi; int /*<<< orphan*/  asi; void* mvdd_control; void* voltage_control; int /*<<< orphan*/  lmp; int /*<<< orphan*/  lhp; int /*<<< orphan*/  rmp; int /*<<< orphan*/  rlp; scalar_t__ ref_div; scalar_t__ max_vddc_in_table; scalar_t__ min_vddc_in_table; scalar_t__ acpi_vddc; } ;
struct TYPE_3__ {scalar_t__ voltage_response_time; scalar_t__ backbias_response_time; struct rv7xx_power_info* priv; } ;
struct TYPE_4__ {scalar_t__ int_thermal_type; TYPE_1__ dpm; } ;
struct radeon_device {int flags; TYPE_2__ pm; } ;
struct atom_clock_dividers {scalar_t__ ref_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ R600_BACKBIASRESPONSETIME_DFLT ; 
 scalar_t__ R600_REFERENCEDIVIDER_DFLT ; 
 scalar_t__ R600_VOLTAGERESPONSETIME_DFLT ; 
 int RADEON_IS_MOBILITY ; 
 int /*<<< orphan*/  RV770_ASI_DFLT ; 
 int /*<<< orphan*/  RV770_HASI_DFLT ; 
 int /*<<< orphan*/  RV770_LHP_DFLT ; 
 int /*<<< orphan*/  RV770_LMP_DFLT ; 
 int /*<<< orphan*/  RV770_RLP_DFLT ; 
 int /*<<< orphan*/  RV770_RMP_DFLT ; 
 int /*<<< orphan*/  RV770_SMC_SOFT_REGISTERS_START ; 
 int /*<<< orphan*/  RV770_SMC_TABLE_ADDRESS ; 
 int /*<<< orphan*/  RV770_VRC_DFLT ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_MVDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ THERMAL_TYPE_NONE ; 
 struct rv7xx_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 void* radeon_atom_is_voltage_gpio (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_get_engine_memory_ss (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_get_max_vddc (struct radeon_device*) ; 
 int rv7xx_parse_power_table (struct radeon_device*) ; 

int rv770_dpm_init(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi;
	struct atom_clock_dividers dividers;
	int ret;

	pi = kzalloc(sizeof(struct rv7xx_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = pi;

	rv770_get_max_vddc(rdev);

	pi->acpi_vddc = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = r600_get_platform_caps(rdev);
	if (ret)
		return ret;

	ret = rv7xx_parse_power_table(rdev);
	if (ret)
		return ret;

	if (rdev->pm.dpm.voltage_response_time == 0)
		rdev->pm.dpm.voltage_response_time = R600_VOLTAGERESPONSETIME_DFLT;
	if (rdev->pm.dpm.backbias_response_time == 0)
		rdev->pm.dpm.backbias_response_time = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &dividers);
	if (ret)
		pi->ref_div = dividers.ref_div + 1;
	else
		pi->ref_div = R600_REFERENCEDIVIDER_DFLT;

	pi->mclk_strobe_mode_threshold = 30000;
	pi->mclk_edc_enable_threshold = 30000;

	pi->rlp = RV770_RLP_DFLT;
	pi->rmp = RV770_RMP_DFLT;
	pi->lhp = RV770_LHP_DFLT;
	pi->lmp = RV770_LMP_DFLT;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_MVDDC, 0);

	rv770_get_engine_memory_ss(rdev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = RV770_HASI_DFLT;
	pi->vrc = RV770_VRC_DFLT;

	pi->power_gating = false;

	pi->gfx_clock_gating = true;

	pi->mg_clock_gating = true;
	pi->mgcgtssm = true;

	pi->dynamic_pcie_gen2 = true;

	if (rdev->pm.int_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	else
		pi->thermal_protection = false;

	pi->display_gap = true;

	if (rdev->flags & RADEON_IS_MOBILITY)
		pi->dcodt = true;
	else
		pi->dcodt = false;

	pi->ulps = true;

	pi->mclk_stutter_mode_threshold = 0;

	pi->sram_end = SMC_RAM_END;
	pi->state_table_start = RV770_SMC_TABLE_ADDRESS;
	pi->soft_regs_start = RV770_SMC_SOFT_REGISTERS_START;

	return 0;
}
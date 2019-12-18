#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rv7xx_power_info {int mclk_strobe_mode_threshold; int mclk_edc_enable_threshold; int power_gating; int gfx_clock_gating; int mg_clock_gating; int mgcgtssm; int dynamic_pcie_gen2; int thermal_protection; int display_gap; int dcodt; int ulps; int /*<<< orphan*/  sram_end; scalar_t__ mclk_stutter_mode_threshold; int /*<<< orphan*/  vrc; int /*<<< orphan*/  pasi; int /*<<< orphan*/  asi; void* mvdd_control; void* voltage_control; int /*<<< orphan*/  lmp; int /*<<< orphan*/  lhp; int /*<<< orphan*/  rmp; int /*<<< orphan*/  rlp; scalar_t__ ref_div; scalar_t__ max_vddc_in_table; scalar_t__ min_vddc_in_table; scalar_t__ acpi_vddc; } ;
struct TYPE_5__ {scalar_t__ voltage_response_time; scalar_t__ backbias_response_time; struct evergreen_power_info* priv; } ;
struct TYPE_6__ {scalar_t__ int_thermal_type; TYPE_2__ dpm; } ;
struct radeon_device {scalar_t__ family; int flags; TYPE_3__ pm; } ;
struct TYPE_4__ {int supported; } ;
struct evergreen_power_info {int mclk_edc_wr_enable_threshold; int ls_clock_gating; int sclk_deep_sleep; int dynamic_ac_timing; int abm; int mcls; int light_sleep; int memory_transition; int pcie_performance_request; int dll_default_on; void* vddci_control; scalar_t__ acpi_vddci; TYPE_1__ ulv; struct rv7xx_power_info rv7xx; } ;
struct atom_clock_dividers {scalar_t__ ref_div; } ;

/* Variables and functions */
 scalar_t__ CHIP_CYPRESS ; 
 scalar_t__ CHIP_HEMLOCK ; 
 scalar_t__ CHIP_JUNIPER ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  CYPRESS_HASI_DFLT ; 
 int /*<<< orphan*/  CYPRESS_VRC_DFLT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ R600_BACKBIASRESPONSETIME_DFLT ; 
 scalar_t__ R600_REFERENCEDIVIDER_DFLT ; 
 scalar_t__ R600_VOLTAGERESPONSETIME_DFLT ; 
 int RADEON_IS_MOBILITY ; 
 int /*<<< orphan*/  RV770_ASI_DFLT ; 
 int /*<<< orphan*/  RV770_LHP_DFLT ; 
 int /*<<< orphan*/  RV770_LMP_DFLT ; 
 int /*<<< orphan*/  RV770_RLP_DFLT ; 
 int /*<<< orphan*/  RV770_RMP_DFLT ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_MVDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDCI ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ THERMAL_TYPE_NONE ; 
 struct evergreen_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int radeon_acpi_is_pcie_performance_request_supported (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 void* radeon_atom_is_voltage_gpio (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_get_engine_memory_ss (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_get_max_vddc (struct radeon_device*) ; 
 int rv7xx_parse_power_table (struct radeon_device*) ; 

int cypress_dpm_init(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi;
	struct evergreen_power_info *eg_pi;
	struct atom_clock_dividers dividers;
	int ret;

	eg_pi = kzalloc(sizeof(struct evergreen_power_info), GFP_KERNEL);
	if (eg_pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = eg_pi;
	pi = &eg_pi->rv7xx;

	rv770_get_max_vddc(rdev);

	eg_pi->ulv.supported = false;
	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
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

	pi->mclk_strobe_mode_threshold = 40000;
	pi->mclk_edc_enable_threshold = 40000;
	eg_pi->mclk_edc_wr_enable_threshold = 40000;

	pi->rlp = RV770_RLP_DFLT;
	pi->rmp = RV770_RMP_DFLT;
	pi->lhp = RV770_LHP_DFLT;
	pi->lmp = RV770_LMP_DFLT;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_MVDDC, 0);

	eg_pi->vddci_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDCI, 0);

	rv770_get_engine_memory_ss(rdev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = CYPRESS_HASI_DFLT;
	pi->vrc = CYPRESS_VRC_DFLT;

	pi->power_gating = false;

	if ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK))
		pi->gfx_clock_gating = false;
	else
		pi->gfx_clock_gating = true;

	pi->mg_clock_gating = true;
	pi->mgcgtssm = true;
	eg_pi->ls_clock_gating = false;
	eg_pi->sclk_deep_sleep = false;

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

	eg_pi->dynamic_ac_timing = true;
	eg_pi->abm = true;
	eg_pi->mcls = true;
	eg_pi->light_sleep = true;
	eg_pi->memory_transition = true;
#if defined(CONFIG_ACPI)
	eg_pi->pcie_performance_request =
		radeon_acpi_is_pcie_performance_request_supported(rdev);
#else
	eg_pi->pcie_performance_request = false;
#endif

	if ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK) ||
	    (rdev->family == CHIP_JUNIPER))
		eg_pi->dll_default_on = true;
	else
		eg_pi->dll_default_on = false;

	eg_pi->sclk_deep_sleep = false;
	pi->mclk_stutter_mode_threshold = 0;

	pi->sram_end = SMC_RAM_END;

	return 0;
}
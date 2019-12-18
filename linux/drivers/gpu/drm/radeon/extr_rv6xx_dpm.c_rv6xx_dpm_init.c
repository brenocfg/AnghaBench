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
struct rv6xx_power_info {int fb_div_scale; int gfx_clock_gating; int sclk_ss; int dynamic_ss; int dynamic_pcie_gen2; int thermal_protection; int display_gap; void* mclk_ss; int /*<<< orphan*/  voltage_control; void* mpll_ref_div; void* spll_ref_div; } ;
struct TYPE_3__ {scalar_t__ voltage_response_time; scalar_t__ backbias_response_time; struct rv6xx_power_info* priv; } ;
struct TYPE_4__ {scalar_t__ int_thermal_type; TYPE_1__ dpm; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ pm; } ;
struct radeon_atom_ss {int dummy; } ;
struct atom_clock_dividers {void* ref_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_ENGINE_SS ; 
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 scalar_t__ CHIP_RV670 ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  COMPUTE_MEMORY_PLL_PARAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ R600_BACKBIASRESPONSETIME_DFLT ; 
 void* R600_REFERENCEDIVIDER_DFLT ; 
 scalar_t__ R600_VOLTAGERESPONSETIME_DFLT ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 scalar_t__ THERMAL_TYPE_NONE ; 
 struct rv6xx_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  radeon_atom_is_voltage_gpio (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rv6xx_parse_power_table (struct radeon_device*) ; 

int rv6xx_dpm_init(struct radeon_device *rdev)
{
	struct radeon_atom_ss ss;
	struct atom_clock_dividers dividers;
	struct rv6xx_power_info *pi;
	int ret;

	pi = kzalloc(sizeof(struct rv6xx_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = pi;

	ret = r600_get_platform_caps(rdev);
	if (ret)
		return ret;

	ret = rv6xx_parse_power_table(rdev);
	if (ret)
		return ret;

	if (rdev->pm.dpm.voltage_response_time == 0)
		rdev->pm.dpm.voltage_response_time = R600_VOLTAGERESPONSETIME_DFLT;
	if (rdev->pm.dpm.backbias_response_time == 0)
		rdev->pm.dpm.backbias_response_time = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &dividers);
	if (ret)
		pi->spll_ref_div = dividers.ref_div + 1;
	else
		pi->spll_ref_div = R600_REFERENCEDIVIDER_DFLT;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     0, false, &dividers);
	if (ret)
		pi->mpll_ref_div = dividers.ref_div + 1;
	else
		pi->mpll_ref_div = R600_REFERENCEDIVIDER_DFLT;

	if (rdev->family >= CHIP_RV670)
		pi->fb_div_scale = 1;
	else
		pi->fb_div_scale = 0;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->gfx_clock_gating = true;

	pi->sclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_ENGINE_SS, 0);
	pi->mclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_MEMORY_SS, 0);

	/* Disable sclk ss, causes hangs on a lot of systems */
	pi->sclk_ss = false;

	if (pi->sclk_ss || pi->mclk_ss)
		pi->dynamic_ss = true;
	else
		pi->dynamic_ss = false;

	pi->dynamic_pcie_gen2 = true;

	if (pi->gfx_clock_gating &&
	    (rdev->pm.int_thermal_type != THERMAL_TYPE_NONE))
		pi->thermal_protection = true;
	else
		pi->thermal_protection = false;

	pi->display_gap = true;

	return 0;
}
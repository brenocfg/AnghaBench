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
struct rv6xx_power_info {scalar_t__ gfx_clock_gating; scalar_t__ dynamic_pcie_gen2; scalar_t__ voltage_control; scalar_t__ thermal_protection; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_6__ {int dpm_thermal; scalar_t__ installed; } ;
struct TYPE_4__ {int platform_caps; struct radeon_ps* boot_ps; } ;
struct TYPE_5__ {int /*<<< orphan*/  int_thermal_type; TYPE_1__ dpm; } ;
struct radeon_device {TYPE_3__ irq; TYPE_2__ pm; } ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_BACKBIAS ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_HIGH ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_LOW ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  r600_dynamicpm_enabled (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_enable_thermal_protection (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_gfx_clockgating_enable (struct radeon_device*,int) ; 
 scalar_t__ r600_is_internal_thermal_sensor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_power_level_enable (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_set_at (struct radeon_device*,int,int,int,int) ; 
 int /*<<< orphan*/  r600_stop_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_wait_for_power_level (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_clear_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_enable_backbias (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_display_gap (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_dynamic_pcie_gen2 (struct radeon_device*,struct radeon_ps*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_spread_spectrum (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_static_voltage_control (struct radeon_device*,struct radeon_ps*,int) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

void rv6xx_dpm_disable(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	if (!r600_dynamicpm_enabled(rdev))
		return;

	r600_power_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
	rv6xx_enable_display_gap(rdev, false);
	rv6xx_clear_vc(rdev);
	r600_set_at(rdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);

	if (pi->thermal_protection)
		r600_enable_thermal_protection(rdev, false);

	r600_wait_for_power_level(rdev, R600_POWER_LEVEL_LOW);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_power_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);

	if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_backbias(rdev, false);

	rv6xx_enable_spread_spectrum(rdev, false);

	if (pi->voltage_control)
		rv6xx_enable_static_voltage_control(rdev, boot_ps, true);

	if (pi->dynamic_pcie_gen2)
		rv6xx_enable_dynamic_pcie_gen2(rdev, boot_ps, false);

	if (rdev->irq.installed &&
	    r600_is_internal_thermal_sensor(rdev->pm.int_thermal_type)) {
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	}

	if (pi->gfx_clock_gating)
		r600_gfx_clockgating_enable(rdev, false);

	r600_stop_dpm(rdev);
}
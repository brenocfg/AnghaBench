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
struct rv7xx_power_info {scalar_t__ mg_clock_gating; scalar_t__ gfx_clock_gating; scalar_t__ dynamic_pcie_gen2; scalar_t__ thermal_protection; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_6__ {int dpm_thermal; scalar_t__ installed; } ;
struct TYPE_4__ {struct radeon_ps* boot_ps; } ;
struct TYPE_5__ {int /*<<< orphan*/  int_thermal_type; TYPE_1__ dpm; } ;
struct radeon_device {TYPE_3__ irq; TYPE_2__ pm; } ;
struct evergreen_power_info {scalar_t__ dynamic_ac_timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  cypress_enable_dynamic_pcie_gen2 (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cypress_enable_spread_spectrum (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cypress_force_mc_use_s1 (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  cypress_gfx_clock_gating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cypress_mg_clock_gating_enable (struct radeon_device*,int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 scalar_t__ r600_is_internal_thermal_sensor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r7xx_stop_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_clear_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_dpm_enabled (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_enable_thermal_protection (struct radeon_device*,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_reset_smio_status (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_stop_dpm (struct radeon_device*) ; 

void cypress_dpm_disable(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	if (!rv770_dpm_enabled(rdev))
		return;

	rv770_clear_vc(rdev);

	if (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, false);

	if (pi->dynamic_pcie_gen2)
		cypress_enable_dynamic_pcie_gen2(rdev, false);

	if (rdev->irq.installed &&
	    r600_is_internal_thermal_sensor(rdev->pm.int_thermal_type)) {
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	}

	if (pi->gfx_clock_gating)
		cypress_gfx_clock_gating_enable(rdev, false);

	if (pi->mg_clock_gating)
		cypress_mg_clock_gating_enable(rdev, false);

	rv770_stop_dpm(rdev);
	r7xx_stop_smc(rdev);

	cypress_enable_spread_spectrum(rdev, false);

	if (eg_pi->dynamic_ac_timing)
		cypress_force_mc_use_s1(rdev, boot_ps);

	rv770_reset_smio_status(rdev);
}
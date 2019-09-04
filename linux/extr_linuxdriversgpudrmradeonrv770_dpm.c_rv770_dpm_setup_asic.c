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
struct rv7xx_power_info {scalar_t__ dcodt; } ;
struct TYPE_4__ {int platform_caps; } ;
struct TYPE_3__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_ASPM_L0s ; 
 int ATOM_PP_PLATFORM_CAP_ASPM_L1 ; 
 int ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1 ; 
 int /*<<< orphan*/  r7xx_read_clock_registers (struct radeon_device*) ; 
 scalar_t__ radeon_aspm ; 
 int /*<<< orphan*/  rv770_enable_acpi_pm (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_enable_l0s (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_enable_l1 (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_enable_pll_sleep_in_l1 (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_get_mclk_odt_threshold (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_get_memory_type (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_get_pcie_gen2_status (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_read_voltage_smio_registers (struct radeon_device*) ; 

void rv770_dpm_setup_asic(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);

	r7xx_read_clock_registers(rdev);
	rv770_read_voltage_smio_registers(rdev);
	rv770_get_memory_type(rdev);
	if (pi->dcodt)
		rv770_get_mclk_odt_threshold(rdev);
	rv770_get_pcie_gen2_status(rdev);

	rv770_enable_acpi_pm(rdev);

	if (radeon_aspm != 0) {
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_ASPM_L0s)
			rv770_enable_l0s(rdev);
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_ASPM_L1)
			rv770_enable_l1(rdev);
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1)
			rv770_enable_pll_sleep_in_l1(rdev);
	}
}
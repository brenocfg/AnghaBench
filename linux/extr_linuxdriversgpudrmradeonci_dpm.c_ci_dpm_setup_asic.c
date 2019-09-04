#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ci_enable_acpi_power_management (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_get_memory_type (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_init_sclk_t (struct radeon_device*) ; 
 int ci_mc_load_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_read_clock_registers (struct radeon_device*) ; 

void ci_dpm_setup_asic(struct radeon_device *rdev)
{
	int r;

	r = ci_mc_load_microcode(rdev);
	if (r)
		DRM_ERROR("Failed to load MC firmware!\n");
	ci_read_clock_registers(rdev);
	ci_get_memory_type(rdev);
	ci_enable_acpi_power_management(rdev);
	ci_init_sclk_t(rdev);
}
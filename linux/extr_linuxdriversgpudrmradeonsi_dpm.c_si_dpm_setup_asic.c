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
 int /*<<< orphan*/  rv770_get_memory_type (struct radeon_device*) ; 
 int /*<<< orphan*/  si_enable_acpi_power_management (struct radeon_device*) ; 
 int si_mc_load_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  si_read_clock_registers (struct radeon_device*) ; 

void si_dpm_setup_asic(struct radeon_device *rdev)
{
	int r;

	r = si_mc_load_microcode(rdev);
	if (r)
		DRM_ERROR("Failed to load MC firmware!\n");
	rv770_get_memory_type(rdev);
	si_read_clock_registers(rdev);
	si_enable_acpi_power_management(rdev);
}
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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_enable_acpi_power_management (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_read_clock_registers (struct amdgpu_device*) ; 

__attribute__((used)) static void si_dpm_setup_asic(struct amdgpu_device *adev)
{
	si_read_clock_registers(adev);
	si_enable_acpi_power_management(adev);
}
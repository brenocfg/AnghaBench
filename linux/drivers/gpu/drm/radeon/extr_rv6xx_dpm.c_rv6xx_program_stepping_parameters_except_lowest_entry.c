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
struct rv6xx_power_info {scalar_t__ voltage_control; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_backbias_stepping_parameters_except_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_mclk_spread_spectrum_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_mclk_stepping_parameters_except_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_memory_timing_parameters (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_sclk_spread_spectrum_parameters_except_lowest_entry (struct radeon_device*) ; 
 int /*<<< orphan*/  rv6xx_program_voltage_stepping_parameters_except_lowest_entry (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_program_stepping_parameters_except_lowest_entry(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_mclk_stepping_parameters_except_lowest_entry(rdev);
	if (pi->voltage_control)
		rv6xx_program_voltage_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_backbias_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_sclk_spread_spectrum_parameters_except_lowest_entry(rdev);
	rv6xx_program_mclk_spread_spectrum_parameters(rdev);
	rv6xx_program_memory_timing_parameters(rdev);
}
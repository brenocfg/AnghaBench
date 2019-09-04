#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sclk; } ;
struct sumo_power_info {TYPE_1__ acpi_pl; } ;
struct radeon_device {int dummy; } ;
struct atom_clock_dividers {int /*<<< orphan*/  post_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_VOLTAGE_EN ; 
 int /*<<< orphan*/  CG_ACPI_CNTL ; 
 int /*<<< orphan*/  CG_ACPI_VOLTAGE_CNTL ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  SCLK_ACPI_DIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_ACPI_DIV_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void sumo_program_acpi_power_level(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct atom_clock_dividers dividers;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     pi->acpi_pl.sclk,
					     false, &dividers);
	if (ret)
		return;

	WREG32_P(CG_ACPI_CNTL, SCLK_ACPI_DIV(dividers.post_div), ~SCLK_ACPI_DIV_MASK);
	WREG32_P(CG_ACPI_VOLTAGE_CNTL, 0, ~ACPI_VOLTAGE_EN);
}
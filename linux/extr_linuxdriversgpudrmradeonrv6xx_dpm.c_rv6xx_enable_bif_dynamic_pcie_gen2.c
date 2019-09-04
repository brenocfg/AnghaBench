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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int LC_HW_VOLTAGE_IF_CONTROL (int) ; 
 int LC_HW_VOLTAGE_IF_CONTROL_MASK ; 
 int /*<<< orphan*/  PCIE_LC_SPEED_CNTL ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rv6xx_enable_bif_dynamic_pcie_gen2(struct radeon_device *rdev,
					       bool enable)
{
	u32 tmp;

	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
	if (enable)
		tmp |= LC_HW_VOLTAGE_IF_CONTROL(1);
	else
		tmp |= LC_HW_VOLTAGE_IF_CONTROL(0);
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, tmp);
}
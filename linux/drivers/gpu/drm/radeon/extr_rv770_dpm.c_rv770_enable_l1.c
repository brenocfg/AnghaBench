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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ASPM_TO_L1_DIS ; 
 int /*<<< orphan*/  LC_L1_INACTIVITY (int) ; 
 int /*<<< orphan*/  LC_L1_INACTIVITY_MASK ; 
 int /*<<< orphan*/  LC_PMI_TO_L1_DIS ; 
 int /*<<< orphan*/  PCIE_LC_CNTL ; 
 int /*<<< orphan*/  RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv770_enable_l1(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	tmp &= ~LC_L1_INACTIVITY_MASK;
	tmp |= LC_L1_INACTIVITY(4);
	tmp &= ~LC_PMI_TO_L1_DIS;
	tmp &= ~LC_ASPM_TO_L1_DIS;
	WREG32_PCIE_PORT(PCIE_LC_CNTL, tmp);
}
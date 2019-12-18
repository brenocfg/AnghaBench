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
 int /*<<< orphan*/  ENABLE_GEN2PCIE ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_enable_bif_dynamic_pcie_gen2 (struct radeon_device*,int) ; 

__attribute__((used)) static void rv770_enable_dynamic_pcie_gen2(struct radeon_device *rdev,
					   bool enable)
{
	rv770_enable_bif_dynamic_pcie_gen2(rdev, enable);

	if (enable)
		WREG32_P(GENERAL_PWRMGT, ENABLE_GEN2PCIE, ~ENABLE_GEN2PCIE);
	else
		WREG32_P(GENERAL_PWRMGT, 0, ~ENABLE_GEN2PCIE);
}
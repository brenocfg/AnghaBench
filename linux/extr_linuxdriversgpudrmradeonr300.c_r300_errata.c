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
struct radeon_device {scalar_t__ family; int /*<<< orphan*/  pll_errata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ERRATA_R300_CG ; 
 scalar_t__ CHIP_R300 ; 
 int RADEON_CFG_ATI_REV_A11 ; 
 int RADEON_CFG_ATI_REV_ID_MASK ; 
 int /*<<< orphan*/  RADEON_CONFIG_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r300_errata(struct radeon_device *rdev)
{
	rdev->pll_errata = 0;

	if (rdev->family == CHIP_R300 &&
	    (RREG32(RADEON_CONFIG_CNTL) & RADEON_CFG_ATI_REV_ID_MASK) == RADEON_CFG_ATI_REV_A11) {
		rdev->pll_errata |= CHIP_ERRATA_R300_CG;
	}
}
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
struct radeon_device {int pll_errata; } ;

/* Variables and functions */
 int CHIP_ERRATA_PLL_DUMMYREADS ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  RADEON_CRTC_GEN_CNTL ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 

void r100_pll_errata_after_index(struct radeon_device *rdev)
{
	if (rdev->pll_errata & CHIP_ERRATA_PLL_DUMMYREADS) {
		(void)RREG32(RADEON_CLOCK_CNTL_DATA);
		(void)RREG32(RADEON_CRTC_GEN_CNTL);
	}
}
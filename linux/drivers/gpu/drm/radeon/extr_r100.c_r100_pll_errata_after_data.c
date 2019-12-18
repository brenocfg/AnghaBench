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
typedef  int uint32_t ;
struct radeon_device {int pll_errata; } ;

/* Variables and functions */
 int CHIP_ERRATA_PLL_DELAY ; 
 int CHIP_ERRATA_R300_CG ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_INDEX ; 
 int RADEON_PLL_WR_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void r100_pll_errata_after_data(struct radeon_device *rdev)
{
	/* This workarounds is necessary on RV100, RS100 and RS200 chips
	 * or the chip could hang on a subsequent access
	 */
	if (rdev->pll_errata & CHIP_ERRATA_PLL_DELAY) {
		mdelay(5);
	}

	/* This function is required to workaround a hardware bug in some (all?)
	 * revisions of the R300.  This workaround should be called after every
	 * CLOCK_CNTL_INDEX register access.  If not, register reads afterward
	 * may not be correct.
	 */
	if (rdev->pll_errata & CHIP_ERRATA_R300_CG) {
		uint32_t save, tmp;

		save = RREG32(RADEON_CLOCK_CNTL_INDEX);
		tmp = save & ~(0x3f | RADEON_PLL_WR_EN);
		WREG32(RADEON_CLOCK_CNTL_INDEX, tmp);
		tmp = RREG32(RADEON_CLOCK_CNTL_DATA);
		WREG32(RADEON_CLOCK_CNTL_INDEX, save);
	}
}
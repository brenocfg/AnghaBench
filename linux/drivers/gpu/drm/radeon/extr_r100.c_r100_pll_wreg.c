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
struct radeon_device {int /*<<< orphan*/  pll_idx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_INDEX ; 
 int RADEON_PLL_WR_EN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r100_pll_errata_after_data (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_pll_errata_after_index (struct radeon_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r100_pll_wreg(struct radeon_device *rdev, uint32_t reg, uint32_t v)
{
	unsigned long flags;

	spin_lock_irqsave(&rdev->pll_idx_lock, flags);
	WREG8(RADEON_CLOCK_CNTL_INDEX, ((reg & 0x3f) | RADEON_PLL_WR_EN));
	r100_pll_errata_after_index(rdev);
	WREG32(RADEON_CLOCK_CNTL_DATA, v);
	r100_pll_errata_after_data(rdev);
	spin_unlock_irqrestore(&rdev->pll_idx_lock, flags);
}
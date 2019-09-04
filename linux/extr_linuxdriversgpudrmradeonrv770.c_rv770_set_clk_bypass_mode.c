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
typedef  scalar_t__ u32 ;
struct radeon_device {int flags; scalar_t__ usec_timeout; scalar_t__ family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SPLL_FUNC_CNTL_2 ; 
 int /*<<< orphan*/  CG_SPLL_STATUS ; 
 scalar_t__ CHIP_RV710 ; 
 scalar_t__ CHIP_RV730 ; 
 int /*<<< orphan*/  MPLL_CNTL_MODE ; 
 scalar_t__ MPLL_MCLK_SEL ; 
 int RADEON_IS_IGP ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ RV730_MPLL_MCLK_SEL ; 
 scalar_t__ SCLK_MUX_SEL (int) ; 
 scalar_t__ SCLK_MUX_SEL_MASK ; 
 scalar_t__ SCLK_MUX_UPDATE ; 
 int SPLL_CHG_STATUS ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rv770_set_clk_bypass_mode(struct radeon_device *rdev)
{
	u32 tmp, i;

	if (rdev->flags & RADEON_IS_IGP)
		return;

	tmp = RREG32(CG_SPLL_FUNC_CNTL_2);
	tmp &= SCLK_MUX_SEL_MASK;
	tmp |= SCLK_MUX_SEL(1) | SCLK_MUX_UPDATE;
	WREG32(CG_SPLL_FUNC_CNTL_2, tmp);

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(CG_SPLL_STATUS) & SPLL_CHG_STATUS)
			break;
		udelay(1);
	}

	tmp &= ~SCLK_MUX_UPDATE;
	WREG32(CG_SPLL_FUNC_CNTL_2, tmp);

	tmp = RREG32(MPLL_CNTL_MODE);
	if ((rdev->family == CHIP_RV710) || (rdev->family == CHIP_RV730))
		tmp &= ~RV730_MPLL_MCLK_SEL;
	else
		tmp &= ~MPLL_MCLK_SEL;
	WREG32(MPLL_CNTL_MODE, tmp);
}
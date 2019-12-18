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
typedef  int uint32_t ;
struct radeon_pll {int reference_freq; } ;
struct TYPE_2__ {struct radeon_pll mpll; } ;
struct radeon_device {TYPE_1__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_MCLK_CNTL ; 
 int RADEON_MPLL_FB_DIV_MASK ; 
 int RADEON_MPLL_FB_DIV_SHIFT ; 
 int RADEON_M_SPLL_REF_DIV_MASK ; 
 int /*<<< orphan*/  RADEON_M_SPLL_REF_FB_DIV ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 

uint32_t radeon_legacy_get_memory_clock(struct radeon_device *rdev)
{
	struct radeon_pll *mpll = &rdev->clock.mpll;
	uint32_t fb_div, ref_div, post_div, mclk;

	fb_div = RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV);
	fb_div = (fb_div >> RADEON_MPLL_FB_DIV_SHIFT) & RADEON_MPLL_FB_DIV_MASK;
	fb_div <<= 1;
	fb_div *= mpll->reference_freq;

	ref_div =
	    RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) & RADEON_M_SPLL_REF_DIV_MASK;

	if (ref_div == 0)
		return 0;

	mclk = fb_div / ref_div;

	post_div = RREG32_PLL(RADEON_MCLK_CNTL) & 0x7;
	if (post_div == 2)
		mclk >>= 1;
	else if (post_div == 3)
		mclk >>= 2;
	else if (post_div == 4)
		mclk >>= 3;

	return mclk;
}
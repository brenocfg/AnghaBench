#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int reference_freq; } ;
struct TYPE_4__ {TYPE_1__ spll; } ;
struct radeon_device {TYPE_2__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SPLL_FUNC_CNTL ; 
 int CURRENT_FEEDBACK_DIV_MASK ; 
 int /*<<< orphan*/  FVTHROT_STATUS_REG0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SPLL_REF_DIV_MASK ; 
 int SPLL_REF_DIV_SHIFT ; 
 int SPLL_SW_HILEN_MASK ; 
 int SPLL_SW_HILEN_SHIFT ; 
 int SPLL_SW_LOLEN_MASK ; 
 int SPLL_SW_LOLEN_SHIFT ; 

u32 rs780_dpm_get_current_sclk(struct radeon_device *rdev)
{
	u32 current_fb_div = RREG32(FVTHROT_STATUS_REG0) & CURRENT_FEEDBACK_DIV_MASK;
	u32 func_cntl = RREG32(CG_SPLL_FUNC_CNTL);
	u32 ref_div = ((func_cntl & SPLL_REF_DIV_MASK) >> SPLL_REF_DIV_SHIFT) + 1;
	u32 post_div = ((func_cntl & SPLL_SW_HILEN_MASK) >> SPLL_SW_HILEN_SHIFT) + 1 +
		((func_cntl & SPLL_SW_LOLEN_MASK) >> SPLL_SW_LOLEN_SHIFT) + 1;
	u32 sclk = (rdev->clock.spll.reference_freq * current_fb_div) /
		(post_div * ref_div);

	return sclk;
}
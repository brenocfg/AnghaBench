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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  current_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct igp_ps {scalar_t__ sclk_low; scalar_t__ sclk_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCED_FEEDBACK_DIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCED_FEEDBACK_DIV_MASK ; 
 int /*<<< orphan*/  FORCE_FEEDBACK_DIV ; 
 int /*<<< orphan*/  FVTHROT_FBDIV_REG1 ; 
 int /*<<< orphan*/  FVTHROT_FBDIV_REG2 ; 
 int /*<<< orphan*/  GFX_MACRO_BYPASS_CNTL ; 
 int /*<<< orphan*/  SPLL_BYPASS_CNTL ; 
 int /*<<< orphan*/  STARTING_FEEDBACK_DIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STARTING_FEEDBACK_DIV_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct igp_ps* rs780_get_ps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rs780_force_fbdiv(struct radeon_device *rdev, u32 fb_div)
{
	struct igp_ps *current_state = rs780_get_ps(rdev->pm.dpm.current_ps);

	if (current_state->sclk_low == current_state->sclk_high)
		return;

	WREG32_P(GFX_MACRO_BYPASS_CNTL, SPLL_BYPASS_CNTL, ~SPLL_BYPASS_CNTL);

	WREG32_P(FVTHROT_FBDIV_REG2, FORCED_FEEDBACK_DIV(fb_div),
		 ~FORCED_FEEDBACK_DIV_MASK);
	WREG32_P(FVTHROT_FBDIV_REG1, STARTING_FEEDBACK_DIV(fb_div),
		 ~STARTING_FEEDBACK_DIV_MASK);
	WREG32_P(FVTHROT_FBDIV_REG1, FORCE_FEEDBACK_DIV, ~FORCE_FEEDBACK_DIV);

	udelay(100);

	WREG32_P(GFX_MACRO_BYPASS_CNTL, 0, ~SPLL_BYPASS_CNTL);
}
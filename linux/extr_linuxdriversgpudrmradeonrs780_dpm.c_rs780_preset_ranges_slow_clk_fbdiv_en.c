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
 int /*<<< orphan*/  FVTHROT_SLOW_CLK_FEEDBACK_DIV_REG1 ; 
 int /*<<< orphan*/  RANGE0_SLOW_CLK_FEEDBACK_DIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RANGE0_SLOW_CLK_FEEDBACK_DIV_MASK ; 
 int /*<<< orphan*/  RANGE_SLOW_CLK_FEEDBACK_DIV_EN ; 
 int /*<<< orphan*/  RS780_SLOWCLKFEEDBACKDIV_DFLT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs780_preset_ranges_slow_clk_fbdiv_en(struct radeon_device *rdev)
{
	WREG32_P(FVTHROT_SLOW_CLK_FEEDBACK_DIV_REG1, RANGE_SLOW_CLK_FEEDBACK_DIV_EN,
		 ~RANGE_SLOW_CLK_FEEDBACK_DIV_EN);

	WREG32_P(FVTHROT_SLOW_CLK_FEEDBACK_DIV_REG1,
		 RANGE0_SLOW_CLK_FEEDBACK_DIV(RS780_SLOWCLKFEEDBACKDIV_DFLT),
		 ~RANGE0_SLOW_CLK_FEEDBACK_DIV_MASK);
}
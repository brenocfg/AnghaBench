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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCLK_FREQ_SETTING_STEP_0_PART2 ; 
 int /*<<< orphan*/  STEP_0_SPLL_ENTRY_VALID ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r600_engine_clock_entry_enable(struct radeon_device *rdev,
				    u32 index, bool enable)
{
	if (enable)
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 STEP_0_SPLL_ENTRY_VALID, ~STEP_0_SPLL_ENTRY_VALID);
	else
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 0, ~STEP_0_SPLL_ENTRY_VALID);
}
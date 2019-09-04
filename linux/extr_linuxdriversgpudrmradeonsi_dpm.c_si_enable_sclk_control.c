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
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  SCLK_PWRMGT_OFF ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_enable_sclk_control(struct radeon_device *rdev, bool enable)
{
	if (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~SCLK_PWRMGT_OFF);
	else
		WREG32_P(SCLK_PWRMGT_CNTL, SCLK_PWRMGT_OFF, ~SCLK_PWRMGT_OFF);

}
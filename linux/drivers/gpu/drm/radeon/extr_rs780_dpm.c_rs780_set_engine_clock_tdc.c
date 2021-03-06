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
 int FORCE_TREND_SEL ; 
 int /*<<< orphan*/  FVTHROT_CNTRL_REG ; 
 int TREND_SEL_MODE ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rs780_set_engine_clock_tdc(struct radeon_device *rdev)
{
	WREG32_P(FVTHROT_CNTRL_REG, 0, ~(FORCE_TREND_SEL | TREND_SEL_MODE));
}
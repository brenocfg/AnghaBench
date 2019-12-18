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
 int FB_DIV_TIMER_VAL (int /*<<< orphan*/ ) ; 
 int FB_DIV_TIMER_VAL_MASK ; 
 int /*<<< orphan*/  FVTHROT_CNTRL_REG ; 
 int /*<<< orphan*/  FVTHROT_FBDIV_REG2 ; 
 int MINIMUM_CIP (int) ; 
 int MINIMUM_CIP_MASK ; 
 int REFRESH_RATE_DIVISOR (int /*<<< orphan*/ ) ; 
 int REFRESH_RATE_DIVISOR_MASK ; 
 int /*<<< orphan*/  RS780_FBDIVTIMERVAL_DFLT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rs780_set_engine_clock_sc(struct radeon_device *rdev)
{
	WREG32_P(FVTHROT_FBDIV_REG2,
		 FB_DIV_TIMER_VAL(RS780_FBDIVTIMERVAL_DFLT),
		 ~FB_DIV_TIMER_VAL_MASK);

	WREG32_P(FVTHROT_CNTRL_REG,
		 REFRESH_RATE_DIVISOR(0) | MINIMUM_CIP(0xf),
		 ~(REFRESH_RATE_DIVISOR_MASK | MINIMUM_CIP_MASK));
}
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
 int /*<<< orphan*/  FVTHROT_FBDIV_REG1 ; 
 int /*<<< orphan*/  FVTHROT_FB_DS_REG0 ; 
 int /*<<< orphan*/  FVTHROT_FB_DS_REG1 ; 
 int /*<<< orphan*/  FVTHROT_FB_US_REG0 ; 
 int /*<<< orphan*/  FVTHROT_FB_US_REG1 ; 
 int /*<<< orphan*/  MAX_FEEDBACK_STEP (int) ; 
 int /*<<< orphan*/  MAX_FEEDBACK_STEP_MASK ; 
 int /*<<< orphan*/  RS780_FVTHROTFBDSREG0_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTFBDSREG1_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTFBUSREG0_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTFBUSREG1_DFLT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs780_set_engine_clock_ssc(struct radeon_device *rdev)
{
	WREG32(FVTHROT_FB_US_REG0, RS780_FVTHROTFBUSREG0_DFLT);
	WREG32(FVTHROT_FB_US_REG1, RS780_FVTHROTFBUSREG1_DFLT);
	WREG32(FVTHROT_FB_DS_REG0, RS780_FVTHROTFBDSREG0_DFLT);
	WREG32(FVTHROT_FB_DS_REG1, RS780_FVTHROTFBDSREG1_DFLT);

	WREG32_P(FVTHROT_FBDIV_REG1, MAX_FEEDBACK_STEP(1), ~MAX_FEEDBACK_STEP_MASK);
}
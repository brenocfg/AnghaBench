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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_TT_EN (int) ; 
 int /*<<< orphan*/  SCLK_TT_EN_MASK ; 
 int /*<<< orphan*/  SMU_SCLK_DPM_TT_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trinity_enable_att(struct radeon_device *rdev)
{
	u32 value = RREG32_SMC(SMU_SCLK_DPM_TT_CNTL);

	value &= ~SCLK_TT_EN_MASK;
	value |= SCLK_TT_EN(1);
	WREG32_SMC(SMU_SCLK_DPM_TT_CNTL, value);
}
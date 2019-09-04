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
 int /*<<< orphan*/  CC_SMU_TST_EFUSE1_MISC ; 
 int /*<<< orphan*/  DYN_PWR_DOWN_EN ; 
 int /*<<< orphan*/  GB_ADDR_CONFIG ; 
 int RB_BACKEND_DISABLE_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  SMU_SCRATCH_A ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void trinity_gfx_powergating_enable(struct radeon_device *rdev,
					   bool enable)
{
	if (enable) {
		if (RREG32_SMC(CC_SMU_TST_EFUSE1_MISC) & RB_BACKEND_DISABLE_MASK)
			WREG32_SMC(SMU_SCRATCH_A, (RREG32_SMC(SMU_SCRATCH_A) | 0x01));

		WREG32_P(SCLK_PWRMGT_CNTL, DYN_PWR_DOWN_EN, ~DYN_PWR_DOWN_EN);
	} else {
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_PWR_DOWN_EN);
		RREG32(GB_ADDR_CONFIG);
	}
}
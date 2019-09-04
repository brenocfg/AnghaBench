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
 int /*<<< orphan*/  CG_CG_VOLTAGE_CNTL ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  GLOBAL_PWRMGT_EN ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SCLK_DPM_BOOT_STATE (int /*<<< orphan*/ ) ; 
 int SCLK_DPM_BOOT_STATE_MASK ; 
 int SCLK_DPM_EN (int) ; 
 int SCLK_DPM_EN_MASK ; 
 int /*<<< orphan*/  SMU_SCLK_DPM_CNTL ; 
 int VOLTAGE_CHG_EN (int) ; 
 int VOLTAGE_CHG_EN_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trinity_dpm_config (struct radeon_device*,int) ; 

__attribute__((used)) static void trinity_start_dpm(struct radeon_device *rdev)
{
	u32 value = RREG32_SMC(SMU_SCLK_DPM_CNTL);

	value &= ~(SCLK_DPM_EN_MASK | SCLK_DPM_BOOT_STATE_MASK | VOLTAGE_CHG_EN_MASK);
	value |= SCLK_DPM_EN(1) | SCLK_DPM_BOOT_STATE(0) | VOLTAGE_CHG_EN(1);
	WREG32_SMC(SMU_SCLK_DPM_CNTL, value);

	WREG32_P(GENERAL_PWRMGT, GLOBAL_PWRMGT_EN, ~GLOBAL_PWRMGT_EN);
	WREG32_P(CG_CG_VOLTAGE_CNTL, 0, ~EN);

	trinity_dpm_config(rdev, true);
}
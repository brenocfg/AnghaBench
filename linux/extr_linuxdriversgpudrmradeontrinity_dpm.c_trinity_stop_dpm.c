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
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SCLK_DPM_EN_MASK ; 
 int /*<<< orphan*/  SMU_SCLK_DPM_CNTL ; 
 int VOLTAGE_CHG_EN_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trinity_dpm_config (struct radeon_device*,int) ; 

__attribute__((used)) static void trinity_stop_dpm(struct radeon_device *rdev)
{
	u32 sclk_dpm_cntl;

	WREG32_P(CG_CG_VOLTAGE_CNTL, EN, ~EN);

	sclk_dpm_cntl = RREG32_SMC(SMU_SCLK_DPM_CNTL);
	sclk_dpm_cntl &= ~(SCLK_DPM_EN_MASK | VOLTAGE_CHG_EN_MASK);
	WREG32_SMC(SMU_SCLK_DPM_CNTL, sclk_dpm_cntl);

	trinity_dpm_config(rdev, false);
}
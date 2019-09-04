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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SCLK_PWRMGT_CNTL__DYNAMIC_PM_EN_MASK ; 
 int SCLK_PWRMGT_CNTL__RESET_BUSY_CNT_MASK ; 
 int SCLK_PWRMGT_CNTL__RESET_SCLK_CNT_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixSCLK_PWRMGT_CNTL ; 

__attribute__((used)) static void kv_start_am(struct amdgpu_device *adev)
{
	u32 sclk_pwrmgt_cntl = RREG32_SMC(ixSCLK_PWRMGT_CNTL);

	sclk_pwrmgt_cntl &= ~(SCLK_PWRMGT_CNTL__RESET_SCLK_CNT_MASK |
			SCLK_PWRMGT_CNTL__RESET_BUSY_CNT_MASK);
	sclk_pwrmgt_cntl |= SCLK_PWRMGT_CNTL__DYNAMIC_PM_EN_MASK;

	WREG32_SMC(ixSCLK_PWRMGT_CNTL, sclk_pwrmgt_cntl);
}
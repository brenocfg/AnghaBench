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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL__SCLK_PWRMGT_OFF_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSCLK_PWRMGT_CNTL ; 

__attribute__((used)) static void ci_enable_sclk_control(struct amdgpu_device *adev, bool enable)
{
	u32 tmp = RREG32_SMC(ixSCLK_PWRMGT_CNTL);

	if (enable)
		tmp &= ~SCLK_PWRMGT_CNTL__SCLK_PWRMGT_OFF_MASK;
	else
		tmp |= SCLK_PWRMGT_CNTL__SCLK_PWRMGT_OFF_MASK;
	WREG32_SMC(ixSCLK_PWRMGT_CNTL, tmp);
}
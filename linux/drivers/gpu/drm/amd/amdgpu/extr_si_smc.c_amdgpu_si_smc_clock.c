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
 int /*<<< orphan*/  CK_DISABLE ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void amdgpu_si_smc_clock(struct amdgpu_device *adev, bool enable)
{
	u32 tmp = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);

	if (enable)
		tmp &= ~CK_DISABLE;
	else
		tmp |= CK_DISABLE;

	WREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0, tmp);
}
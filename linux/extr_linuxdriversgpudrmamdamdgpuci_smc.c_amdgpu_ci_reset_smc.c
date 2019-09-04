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
 int /*<<< orphan*/  SMC_SYSCON_RESET_CNTL__rst_reg_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixSMC_SYSCON_RESET_CNTL ; 

void amdgpu_ci_reset_smc(struct amdgpu_device *adev)
{
	u32 tmp = RREG32_SMC(ixSMC_SYSCON_RESET_CNTL);

	tmp |= SMC_SYSCON_RESET_CNTL__rst_reg_MASK;
	WREG32_SMC(ixSMC_SYSCON_RESET_CNTL, tmp);
}
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
 int /*<<< orphan*/  RST_REG ; 
 int /*<<< orphan*/  SMC_SYSCON_RESET_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ci_reset_smc(struct radeon_device *rdev)
{
	u32 tmp = RREG32_SMC(SMC_SYSCON_RESET_CNTL);

	tmp |= RST_REG;
	WREG32_SMC(SMC_SYSCON_RESET_CNTL, tmp);
}
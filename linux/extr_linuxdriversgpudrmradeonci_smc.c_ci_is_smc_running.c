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
 int CK_DISABLE ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_PC_C ; 
 int /*<<< orphan*/  SMC_SYSCON_CLOCK_CNTL_0 ; 

bool ci_is_smc_running(struct radeon_device *rdev)
{
	u32 clk = RREG32_SMC(SMC_SYSCON_CLOCK_CNTL_0);
	u32 pc_c = RREG32_SMC(SMC_PC_C);

	if (!(clk & CK_DISABLE) && (0x20100 <= pc_c))
		return true;

	return false;
}
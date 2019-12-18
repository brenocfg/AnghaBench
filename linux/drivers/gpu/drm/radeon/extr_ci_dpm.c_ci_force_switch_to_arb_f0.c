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
 int MC_CG_ARB_FREQ_F0 ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SCRATCH9 ; 
 int ni_copy_and_switch_arb_sets (struct radeon_device*,int,int) ; 

__attribute__((used)) static int ci_force_switch_to_arb_f0(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = (RREG32_SMC(SMC_SCRATCH9) & 0x0000ff00) >> 8;

	if (tmp == MC_CG_ARB_FREQ_F0)
		return 0;

	return ni_copy_and_switch_arb_sets(rdev, tmp, MC_CG_ARB_FREQ_F0);
}
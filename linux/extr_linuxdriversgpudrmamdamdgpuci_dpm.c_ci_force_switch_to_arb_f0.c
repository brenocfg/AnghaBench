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
 int MC_CG_ARB_FREQ_F0 ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int ci_copy_and_switch_arb_sets (struct amdgpu_device*,int,int) ; 
 int /*<<< orphan*/  ixSMC_SCRATCH9 ; 

__attribute__((used)) static int ci_force_switch_to_arb_f0(struct amdgpu_device *adev)
{
	u32 tmp;

	tmp = (RREG32_SMC(ixSMC_SCRATCH9) & 0x0000ff00) >> 8;

	if (tmp == MC_CG_ARB_FREQ_F0)
		return 0;

	return ci_copy_and_switch_arb_sets(adev, tmp, MC_CG_ARB_FREQ_F0);
}
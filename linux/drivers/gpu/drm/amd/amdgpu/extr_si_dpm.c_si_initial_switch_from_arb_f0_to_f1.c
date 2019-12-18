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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F0 ; 
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F1 ; 
 int ni_copy_and_switch_arb_sets (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_initial_switch_from_arb_f0_to_f1(struct amdgpu_device *adev)
{
	return ni_copy_and_switch_arb_sets(adev, MC_CG_ARB_FREQ_F0, MC_CG_ARB_FREQ_F1);
}
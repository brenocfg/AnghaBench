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
 int CG_STATIC_SCREEN_PARAMETER__STATIC_SCREEN_THRESHOLD_UNIT__SHIFT ; 
 int CG_STATIC_SCREEN_PARAMETER__STATIC_SCREEN_THRESHOLD__SHIFT ; 
 int CISLANDS_SSTU_DFLT ; 
 int CISLANDS_SST_DFLT ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixCG_STATIC_SCREEN_PARAMETER ; 

__attribute__((used)) static void ci_program_sstp(struct amdgpu_device *adev)
{
	WREG32_SMC(ixCG_STATIC_SCREEN_PARAMETER,
	((CISLANDS_SSTU_DFLT << CG_STATIC_SCREEN_PARAMETER__STATIC_SCREEN_THRESHOLD_UNIT__SHIFT) |
	 (CISLANDS_SST_DFLT << CG_STATIC_SCREEN_PARAMETER__STATIC_SCREEN_THRESHOLD__SHIFT)));
}
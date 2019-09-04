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
 int CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK ; 
 int CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixCG_MULT_THERMAL_STATUS ; 

__attribute__((used)) static int ci_dpm_get_temp(void *handle)
{
	u32 temp;
	int actual_temp = 0;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	temp = (RREG32_SMC(ixCG_MULT_THERMAL_STATUS) & CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK) >>
		CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT;

	if (temp & 0x200)
		actual_temp = 255;
	else
		actual_temp = temp & 0x1ff;

	actual_temp = actual_temp * 1000;

	return actual_temp;
}
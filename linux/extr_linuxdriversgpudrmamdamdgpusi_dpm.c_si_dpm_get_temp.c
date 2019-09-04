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
 int /*<<< orphan*/  CG_MULT_THERMAL_STATUS ; 
 int CTF_TEMP_MASK ; 
 int CTF_TEMP_SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_dpm_get_temp(void *handle)
{
	u32 temp;
	int actual_temp = 0;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	temp = (RREG32(CG_MULT_THERMAL_STATUS) & CTF_TEMP_MASK) >>
		CTF_TEMP_SHIFT;

	if (temp & 0x200)
		actual_temp = 255;
	else
		actual_temp = temp & 0x1ff;

	actual_temp = (actual_temp * 1000);

	return actual_temp;
}
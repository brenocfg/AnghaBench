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
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK ; 
 int CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT ; 
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THM ; 
 int /*<<< orphan*/  mmCG_MULT_THERMAL_STATUS ; 

int vega10_thermal_get_temperature(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	int temp;

	temp = RREG32_SOC15(THM, 0, mmCG_MULT_THERMAL_STATUS);

	temp = (temp & CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK) >>
			CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT;

	temp = temp & 0x1ff;

	temp *= PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return temp;
}
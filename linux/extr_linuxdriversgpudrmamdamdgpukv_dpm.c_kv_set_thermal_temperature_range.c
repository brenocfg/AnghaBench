#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int min_temp; int max_temp; } ;
struct TYPE_5__ {TYPE_1__ thermal; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int CG_THERMAL_INT_CTRL__DIG_THERM_INTH_MASK ; 
 int CG_THERMAL_INT_CTRL__DIG_THERM_INTH__SHIFT ; 
 int CG_THERMAL_INT_CTRL__DIG_THERM_INTL_MASK ; 
 int CG_THERMAL_INT_CTRL__DIG_THERM_INTL__SHIFT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixCG_THERMAL_INT_CTRL ; 

__attribute__((used)) static int kv_set_thermal_temperature_range(struct amdgpu_device *adev,
					    int min_temp, int max_temp)
{
	int low_temp = 0 * 1000;
	int high_temp = 255 * 1000;
	u32 tmp;

	if (low_temp < min_temp)
		low_temp = min_temp;
	if (high_temp > max_temp)
		high_temp = max_temp;
	if (high_temp < low_temp) {
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		return -EINVAL;
	}

	tmp = RREG32_SMC(ixCG_THERMAL_INT_CTRL);
	tmp &= ~(CG_THERMAL_INT_CTRL__DIG_THERM_INTH_MASK |
		CG_THERMAL_INT_CTRL__DIG_THERM_INTL_MASK);
	tmp |= ((49 + (high_temp / 1000)) << CG_THERMAL_INT_CTRL__DIG_THERM_INTH__SHIFT) |
		((49 + (low_temp / 1000)) << CG_THERMAL_INT_CTRL__DIG_THERM_INTL__SHIFT);
	WREG32_SMC(ixCG_THERMAL_INT_CTRL, tmp);

	adev->pm.dpm.thermal.min_temp = low_temp;
	adev->pm.dpm.thermal.max_temp = high_temp;

	return 0;
}
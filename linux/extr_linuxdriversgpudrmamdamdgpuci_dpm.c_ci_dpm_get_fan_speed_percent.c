#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ no_fan; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int CG_FDO_CTRL1__FMAX_DUTY100_MASK ; 
 int CG_FDO_CTRL1__FMAX_DUTY100__SHIFT ; 
 int CG_THERMAL_STATUS__FDO_PWM_DUTY_MASK ; 
 int CG_THERMAL_STATUS__FDO_PWM_DUTY__SHIFT ; 
 int EINVAL ; 
 int ENOENT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  ixCG_FDO_CTRL1 ; 
 int /*<<< orphan*/  ixCG_THERMAL_STATUS ; 

__attribute__((used)) static int ci_dpm_get_fan_speed_percent(void *handle,
					u32 *speed)
{
	u32 duty, duty100;
	u64 tmp64;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->pm.no_fan)
		return -ENOENT;

	duty100 = (RREG32_SMC(ixCG_FDO_CTRL1) & CG_FDO_CTRL1__FMAX_DUTY100_MASK)
		>> CG_FDO_CTRL1__FMAX_DUTY100__SHIFT;
	duty = (RREG32_SMC(ixCG_THERMAL_STATUS) & CG_THERMAL_STATUS__FDO_PWM_DUTY_MASK)
		>> CG_THERMAL_STATUS__FDO_PWM_DUTY__SHIFT;

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (u64)duty * 100;
	do_div(tmp64, duty100);
	*speed = (u32)tmp64;

	if (*speed > 100)
		*speed = 100;

	return 0;
}
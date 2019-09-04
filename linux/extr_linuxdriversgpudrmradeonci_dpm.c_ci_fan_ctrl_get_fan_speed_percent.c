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
struct radeon_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL1 ; 
 int /*<<< orphan*/  CG_THERMAL_STATUS ; 
 int EINVAL ; 
 int ENOENT ; 
 int FDO_PWM_DUTY_MASK ; 
 int FDO_PWM_DUTY_SHIFT ; 
 int FMAX_DUTY100_MASK ; 
 int FMAX_DUTY100_SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

int ci_fan_ctrl_get_fan_speed_percent(struct radeon_device *rdev,
					     u32 *speed)
{
	u32 duty, duty100;
	u64 tmp64;

	if (rdev->pm.no_fan)
		return -ENOENT;

	duty100 = (RREG32_SMC(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;
	duty = (RREG32_SMC(CG_THERMAL_STATUS) & FDO_PWM_DUTY_MASK) >> FDO_PWM_DUTY_SHIFT;

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (u64)duty * 100;
	do_div(tmp64, duty100);
	*speed = (u32)tmp64;

	if (*speed > 100)
		*speed = 100;

	return 0;
}
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
struct ci_power_info {scalar_t__ fan_is_controlled_by_smc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL0 ; 
 int /*<<< orphan*/  CG_FDO_CTRL1 ; 
 int EINVAL ; 
 int ENOENT ; 
 int FDO_STATIC_DUTY (int) ; 
 int FDO_STATIC_DUTY_MASK ; 
 int FMAX_DUTY100_MASK ; 
 int FMAX_DUTY100_SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

int ci_fan_ctrl_set_fan_speed_percent(struct radeon_device *rdev,
					     u32 speed)
{
	u32 tmp;
	u32 duty, duty100;
	u64 tmp64;
	struct ci_power_info *pi = ci_get_pi(rdev);

	if (rdev->pm.no_fan)
		return -ENOENT;

	if (pi->fan_is_controlled_by_smc)
		return -EINVAL;

	if (speed > 100)
		return -EINVAL;

	duty100 = (RREG32_SMC(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (u64)speed * duty100;
	do_div(tmp64, 100);
	duty = (u32)tmp64;

	tmp = RREG32_SMC(CG_FDO_CTRL0) & ~FDO_STATIC_DUTY_MASK;
	tmp |= FDO_STATIC_DUTY(duty);
	WREG32_SMC(CG_FDO_CTRL0, tmp);

	return 0;
}
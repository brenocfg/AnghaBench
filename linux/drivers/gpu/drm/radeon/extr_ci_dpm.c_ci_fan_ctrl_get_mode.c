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
struct radeon_device {int dummy; } ;
struct ci_power_info {scalar_t__ fan_is_controlled_by_smc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL2 ; 
 int FDO_PWM_MODE_MASK ; 
 int FDO_PWM_MODE_SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

u32 ci_fan_ctrl_get_mode(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp;

	if (pi->fan_is_controlled_by_smc)
		return 0;

	tmp = RREG32_SMC(CG_FDO_CTRL2) & FDO_PWM_MODE_MASK;
	return (tmp >> FDO_PWM_MODE_SHIFT);
}
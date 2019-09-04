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
struct ci_power_info {scalar_t__ fan_is_controlled_by_smc; } ;
struct TYPE_2__ {scalar_t__ no_fan; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int CG_FDO_CTRL0__FDO_STATIC_DUTY_MASK ; 
 int CG_FDO_CTRL0__FDO_STATIC_DUTY__SHIFT ; 
 int CG_FDO_CTRL1__FMAX_DUTY100_MASK ; 
 int CG_FDO_CTRL1__FMAX_DUTY100__SHIFT ; 
 int EINVAL ; 
 int ENOENT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  ixCG_FDO_CTRL0 ; 
 int /*<<< orphan*/  ixCG_FDO_CTRL1 ; 

__attribute__((used)) static int ci_dpm_set_fan_speed_percent(void *handle,
					u32 speed)
{
	u32 tmp;
	u32 duty, duty100;
	u64 tmp64;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);

	if (adev->pm.no_fan)
		return -ENOENT;

	if (pi->fan_is_controlled_by_smc)
		return -EINVAL;

	if (speed > 100)
		return -EINVAL;

	duty100 = (RREG32_SMC(ixCG_FDO_CTRL1) & CG_FDO_CTRL1__FMAX_DUTY100_MASK)
		>> CG_FDO_CTRL1__FMAX_DUTY100__SHIFT;

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (u64)speed * duty100;
	do_div(tmp64, 100);
	duty = (u32)tmp64;

	tmp = RREG32_SMC(ixCG_FDO_CTRL0) & ~CG_FDO_CTRL0__FDO_STATIC_DUTY_MASK;
	tmp |= duty << CG_FDO_CTRL0__FDO_STATIC_DUTY__SHIFT;
	WREG32_SMC(ixCG_FDO_CTRL0, tmp);

	return 0;
}
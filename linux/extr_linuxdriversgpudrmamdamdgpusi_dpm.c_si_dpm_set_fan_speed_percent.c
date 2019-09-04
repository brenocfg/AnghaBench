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
struct si_power_info {scalar_t__ fan_is_controlled_by_smc; } ;
struct TYPE_2__ {scalar_t__ no_fan; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL0 ; 
 int /*<<< orphan*/  CG_FDO_CTRL1 ; 
 int EINVAL ; 
 int ENOENT ; 
 int FDO_STATIC_DUTY (int) ; 
 int FDO_STATIC_DUTY_MASK ; 
 int FMAX_DUTY100_MASK ; 
 int FMAX_DUTY100_SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dpm_set_fan_speed_percent(void *handle,
				      u32 speed)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct si_power_info *si_pi = si_get_pi(adev);
	u32 tmp;
	u32 duty, duty100;
	u64 tmp64;

	if (adev->pm.no_fan)
		return -ENOENT;

	if (si_pi->fan_is_controlled_by_smc)
		return -EINVAL;

	if (speed > 100)
		return -EINVAL;

	duty100 = (RREG32(CG_FDO_CTRL1) & FMAX_DUTY100_MASK) >> FMAX_DUTY100_SHIFT;

	if (duty100 == 0)
		return -EINVAL;

	tmp64 = (u64)speed * duty100;
	do_div(tmp64, 100);
	duty = (u32)tmp64;

	tmp = RREG32(CG_FDO_CTRL0) & ~FDO_STATIC_DUTY_MASK;
	tmp |= FDO_STATIC_DUTY(duty);
	WREG32(CG_FDO_CTRL0, tmp);

	return 0;
}
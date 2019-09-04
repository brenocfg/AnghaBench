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
struct ci_power_info {int fan_ctrl_is_in_default_mode; int fan_ctrl_default_mode; int t_min; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int CG_FDO_CTRL2__FDO_PWM_MODE_MASK ; 
 int CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT ; 
 int CG_FDO_CTRL2__TMIN_MASK ; 
 int CG_FDO_CTRL2__TMIN__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixCG_FDO_CTRL2 ; 

__attribute__((used)) static void ci_fan_ctrl_set_default_mode(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 tmp;

	if (!pi->fan_ctrl_is_in_default_mode) {
		tmp = RREG32_SMC(ixCG_FDO_CTRL2) & ~CG_FDO_CTRL2__FDO_PWM_MODE_MASK;
		tmp |= pi->fan_ctrl_default_mode << CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT;
		WREG32_SMC(ixCG_FDO_CTRL2, tmp);

		tmp = RREG32_SMC(ixCG_FDO_CTRL2) & ~CG_FDO_CTRL2__TMIN_MASK;
		tmp |= pi->t_min << CG_FDO_CTRL2__TMIN__SHIFT;
		WREG32_SMC(ixCG_FDO_CTRL2, tmp);
		pi->fan_ctrl_is_in_default_mode = true;
	}
}
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
typedef  int u32 ;
struct TYPE_2__ {int fan_pulses_per_revolution; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int CG_FDO_CTRL2__TACH_PWM_RESP_RATE_MASK ; 
 int CG_FDO_CTRL2__TACH_PWM_RESP_RATE__SHIFT ; 
 int CG_TACH_CTRL__EDGE_PER_REV_MASK ; 
 int CG_TACH_CTRL__EDGE_PER_REV__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixCG_FDO_CTRL2 ; 
 int /*<<< orphan*/  ixCG_TACH_CTRL ; 

__attribute__((used)) static void ci_thermal_initialize(struct amdgpu_device *adev)
{
	u32 tmp;

	if (adev->pm.fan_pulses_per_revolution) {
		tmp = RREG32_SMC(ixCG_TACH_CTRL) & ~CG_TACH_CTRL__EDGE_PER_REV_MASK;
		tmp |= (adev->pm.fan_pulses_per_revolution - 1)
			<< CG_TACH_CTRL__EDGE_PER_REV__SHIFT;
		WREG32_SMC(ixCG_TACH_CTRL, tmp);
	}

	tmp = RREG32_SMC(ixCG_FDO_CTRL2) & ~CG_FDO_CTRL2__TACH_PWM_RESP_RATE_MASK;
	tmp |= 0x28 << CG_FDO_CTRL2__TACH_PWM_RESP_RATE__SHIFT;
	WREG32_SMC(ixCG_FDO_CTRL2, tmp);
}
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
struct TYPE_2__ {scalar_t__ fan_pulses_per_revolution; } ;
struct amdgpu_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL2 ; 
 int /*<<< orphan*/  CG_TACH_CTRL ; 
 int EDGE_PER_REV (scalar_t__) ; 
 int EDGE_PER_REV_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int TACH_PWM_RESP_RATE (int) ; 
 int TACH_PWM_RESP_RATE_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_thermal_initialize(struct amdgpu_device *adev)
{
	u32 tmp;

	if (adev->pm.fan_pulses_per_revolution) {
		tmp = RREG32(CG_TACH_CTRL) & ~EDGE_PER_REV_MASK;
		tmp |= EDGE_PER_REV(adev->pm.fan_pulses_per_revolution -1);
		WREG32(CG_TACH_CTRL, tmp);
	}

	tmp = RREG32(CG_FDO_CTRL2) & ~TACH_PWM_RESP_RATE_MASK;
	tmp |= TACH_PWM_RESP_RATE(0x28);
	WREG32(CG_FDO_CTRL2, tmp);
}
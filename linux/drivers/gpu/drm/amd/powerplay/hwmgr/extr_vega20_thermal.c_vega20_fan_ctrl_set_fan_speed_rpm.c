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
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_TACH_CTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  FDO_PWM_MODE_STATIC_RPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PERIOD ; 
 int /*<<< orphan*/  THM ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_asic_get_xclk (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCG_TACH_CTRL ; 
 int vega20_fan_ctrl_set_static_mode (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int vega20_fan_ctrl_stop_smc_fan_control (struct pp_hwmgr*) ; 

int vega20_fan_ctrl_set_fan_speed_rpm(struct pp_hwmgr *hwmgr, uint32_t speed)
{
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t tach_period, crystal_clock_freq;
	int result = 0;

	if (!speed)
		return -EINVAL;

	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl)) {
		result = vega20_fan_ctrl_stop_smc_fan_control(hwmgr);
		if (result)
			return result;
	}

	crystal_clock_freq = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);
	tach_period = 60 * crystal_clock_freq * 10000 / (8 * speed);
	WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
				CG_TACH_CTRL, TARGET_PERIOD,
				tach_period));

	return vega20_fan_ctrl_set_static_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int ulMinRPM; int ulMaxRPM; scalar_t__ bNoFan; } ;
struct TYPE_4__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {struct amdgpu_device* adev; TYPE_2__ thermal_controller; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_TACH_CTRL ; 
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
 int vega10_fan_ctrl_set_static_mode (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int vega10_fan_ctrl_stop_smc_fan_control (struct pp_hwmgr*) ; 

int vega10_fan_ctrl_set_fan_speed_rpm(struct pp_hwmgr *hwmgr, uint32_t speed)
{
	struct amdgpu_device *adev = hwmgr->adev;
	uint32_t tach_period;
	uint32_t crystal_clock_freq;
	int result = 0;

	if (hwmgr->thermal_controller.fanInfo.bNoFan ||
	    speed == 0 ||
	    (speed < hwmgr->thermal_controller.fanInfo.ulMinRPM) ||
	    (speed > hwmgr->thermal_controller.fanInfo.ulMaxRPM))
		return -1;

	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		result = vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

	if (!result) {
		crystal_clock_freq = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);
		tach_period = 60 * crystal_clock_freq * 10000 / (8 * speed);
		WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
				REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
					CG_TACH_CTRL, TARGET_PERIOD,
					tach_period));
	}
	return vega10_fan_ctrl_set_static_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
}
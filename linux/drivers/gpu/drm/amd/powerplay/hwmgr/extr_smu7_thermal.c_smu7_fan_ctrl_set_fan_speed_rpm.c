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
struct TYPE_3__ {scalar_t__ ucTachometerPulsesPerRevolution; int ulMinRPM; int ulMaxRPM; scalar_t__ bNoFan; } ;
struct TYPE_4__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ adev; TYPE_2__ thermal_controller; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_TACH_CTRL ; 
 int /*<<< orphan*/  FDO_PWM_MODE_STATIC_RPM ; 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PERIOD ; 
 int amdgpu_asic_get_xclk (struct amdgpu_device*) ; 
 int smu7_fan_ctrl_set_static_mode (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_fan_ctrl_stop_smc_fan_control (struct pp_hwmgr*) ; 

int smu7_fan_ctrl_set_fan_speed_rpm(struct pp_hwmgr *hwmgr, uint32_t speed)
{
	uint32_t tach_period;
	uint32_t crystal_clock_freq;

	if (hwmgr->thermal_controller.fanInfo.bNoFan ||
			(hwmgr->thermal_controller.fanInfo.
			ucTachometerPulsesPerRevolution == 0) ||
			speed == 0 ||
			(speed < hwmgr->thermal_controller.fanInfo.ulMinRPM) ||
			(speed > hwmgr->thermal_controller.fanInfo.ulMaxRPM))
		return 0;

	if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
		smu7_fan_ctrl_stop_smc_fan_control(hwmgr);

	crystal_clock_freq = amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);

	tach_period = 60 * crystal_clock_freq * 10000 / (8 * speed);

	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_TACH_CTRL, TARGET_PERIOD, tach_period);

	return smu7_fan_ctrl_set_static_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
}
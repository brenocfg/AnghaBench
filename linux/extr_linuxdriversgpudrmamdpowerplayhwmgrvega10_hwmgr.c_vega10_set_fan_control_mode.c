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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
#define  AMD_FAN_CTRL_AUTO 130 
#define  AMD_FAN_CTRL_MANUAL 129 
#define  AMD_FAN_CTRL_NONE 128 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 int /*<<< orphan*/  PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega10_fan_ctrl_set_fan_speed_percent (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  vega10_fan_ctrl_start_smc_fan_control (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  vega10_fan_ctrl_stop_smc_fan_control (struct pp_hwmgr*) ; 

__attribute__((used)) static void vega10_set_fan_control_mode(struct pp_hwmgr *hwmgr, uint32_t mode)
{
	switch (mode) {
	case AMD_FAN_CTRL_NONE:
		vega10_fan_ctrl_set_fan_speed_percent(hwmgr, 100);
		break;
	case AMD_FAN_CTRL_MANUAL:
		if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
			vega10_fan_ctrl_stop_smc_fan_control(hwmgr);
		break;
	case AMD_FAN_CTRL_AUTO:
		if (PP_CAP(PHM_PlatformCaps_MicrocodeFanControl))
			vega10_fan_ctrl_start_smc_fan_control(hwmgr);
		break;
	default:
		break;
	}
}
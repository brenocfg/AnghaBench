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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; } ;

/* Variables and functions */
#define  AMD_FAN_CTRL_AUTO 130 
#define  AMD_FAN_CTRL_MANUAL 129 
#define  AMD_FAN_CTRL_NONE 128 
 int /*<<< orphan*/  PHM_PlatformCaps_MicrocodeFanControl ; 
 int /*<<< orphan*/  phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_fan_ctrl_set_fan_speed_percent (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  smu7_fan_ctrl_set_static_mode (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  smu7_fan_ctrl_start_smc_fan_control (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_fan_ctrl_stop_smc_fan_control (struct pp_hwmgr*) ; 

__attribute__((used)) static void smu7_set_fan_control_mode(struct pp_hwmgr *hwmgr, uint32_t mode)
{
	switch (mode) {
	case AMD_FAN_CTRL_NONE:
		smu7_fan_ctrl_set_fan_speed_percent(hwmgr, 100);
		break;
	case AMD_FAN_CTRL_MANUAL:
		if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_MicrocodeFanControl))
			smu7_fan_ctrl_stop_smc_fan_control(hwmgr);
		break;
	case AMD_FAN_CTRL_AUTO:
		if (!smu7_fan_ctrl_set_static_mode(hwmgr, mode))
			smu7_fan_ctrl_start_smc_fan_control(hwmgr);
		break;
	default:
		break;
	}
}
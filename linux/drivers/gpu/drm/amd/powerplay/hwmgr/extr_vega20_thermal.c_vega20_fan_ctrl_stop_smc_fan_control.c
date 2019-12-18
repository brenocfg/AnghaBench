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
struct vega20_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {struct vega20_hwmgr* backend; } ;
struct TYPE_2__ {scalar_t__ supported; } ;

/* Variables and functions */
 size_t GNLD_FAN_CONTROL ; 
 int vega20_disable_fan_control_feature (struct pp_hwmgr*) ; 

int vega20_fan_ctrl_stop_smc_fan_control(struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data = hwmgr->backend;

	if (data->smu_features[GNLD_FAN_CONTROL].supported)
		return vega20_disable_fan_control_feature(hwmgr);

	return 0;
}
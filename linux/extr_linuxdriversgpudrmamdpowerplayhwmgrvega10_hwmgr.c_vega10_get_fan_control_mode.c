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
typedef  int /*<<< orphan*/  uint32_t ;
struct vega10_hwmgr {TYPE_1__* smu_features; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_FAN_CTRL_AUTO ; 
 int /*<<< orphan*/  AMD_FAN_CTRL_MANUAL ; 
 size_t GNLD_FAN_CONTROL ; 

__attribute__((used)) static uint32_t vega10_get_fan_control_mode(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->smu_features[GNLD_FAN_CONTROL].enabled == false)
		return AMD_FAN_CTRL_MANUAL;
	else
		return AMD_FAN_CTRL_AUTO;
}
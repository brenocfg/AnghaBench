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
struct TYPE_3__ {int /*<<< orphan*/  bNoFan; } ;
struct TYPE_4__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {TYPE_2__ thermal_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu7_fan_ctrl_set_default_mode (struct pp_hwmgr*) ; 

int smu7_thermal_ctrl_uninitialize_thermal_controller(struct pp_hwmgr *hwmgr)
{
	if (!hwmgr->thermal_controller.fanInfo.bNoFan)
		smu7_fan_ctrl_set_default_mode(hwmgr);
	return 0;
}
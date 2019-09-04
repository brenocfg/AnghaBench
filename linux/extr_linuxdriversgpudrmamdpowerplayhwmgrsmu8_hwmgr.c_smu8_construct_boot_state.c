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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int allowGnbSlow; scalar_t__ vce_wm; scalar_t__ display_wm; scalar_t__ numSIMDToPowerDown; scalar_t__ hysteresis_up; scalar_t__ forceNBPstate; scalar_t__ ssDividerIndex; scalar_t__ dsDividerIndex; scalar_t__ vddcIndex; int /*<<< orphan*/  engineClock; } ;
struct TYPE_3__ {scalar_t__ bootup_nb_voltage_index; int /*<<< orphan*/  bootup_engine_clock; } ;
struct smu8_hwmgr {TYPE_2__ boot_power_level; TYPE_1__ sys_info; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */

__attribute__((used)) static int smu8_construct_boot_state(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	data->boot_power_level.engineClock =
				data->sys_info.bootup_engine_clock;

	data->boot_power_level.vddcIndex =
			(uint8_t)data->sys_info.bootup_nb_voltage_index;

	data->boot_power_level.dsDividerIndex = 0;
	data->boot_power_level.ssDividerIndex = 0;
	data->boot_power_level.allowGnbSlow = 1;
	data->boot_power_level.forceNBPstate = 0;
	data->boot_power_level.hysteresis_up = 0;
	data->boot_power_level.numSIMDToPowerDown = 0;
	data->boot_power_level.display_wm = 0;
	data->boot_power_level.vce_wm = 0;

	return 0;
}
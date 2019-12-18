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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ cpu_pstate_separation_time; int cpu_cc6_disable; int cpu_pstate_disable; int nb_pstate_switch_disable; int cc6_setting_changed; } ;
struct smu8_hwmgr {TYPE_1__ cc6_settings; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */

__attribute__((used)) static int smu8_store_cc6_data(struct pp_hwmgr *hwmgr, uint32_t separation_time,
			bool cc6_disable, bool pstate_disable, bool pstate_switch_disable)
{
	struct smu8_hwmgr *hw_data = hwmgr->backend;

	if (separation_time !=
	    hw_data->cc6_settings.cpu_pstate_separation_time ||
	    cc6_disable != hw_data->cc6_settings.cpu_cc6_disable ||
	    pstate_disable != hw_data->cc6_settings.cpu_pstate_disable ||
	    pstate_switch_disable != hw_data->cc6_settings.nb_pstate_switch_disable) {

		hw_data->cc6_settings.cc6_setting_changed = true;

		hw_data->cc6_settings.cpu_pstate_separation_time =
			separation_time;
		hw_data->cc6_settings.cpu_cc6_disable =
			cc6_disable;
		hw_data->cc6_settings.cpu_pstate_disable =
			pstate_disable;
		hw_data->cc6_settings.nb_pstate_switch_disable =
			pstate_switch_disable;

	}

	return 0;
}
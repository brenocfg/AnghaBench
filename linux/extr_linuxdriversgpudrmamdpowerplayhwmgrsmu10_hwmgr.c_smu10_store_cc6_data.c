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
typedef  scalar_t__ uint32_t ;
struct smu10_hwmgr {scalar_t__ separation_time; int cc6_disable; int pstate_disable; int cc6_setting_changed; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */

__attribute__((used)) static int smu10_store_cc6_data(struct pp_hwmgr *hwmgr, uint32_t separation_time,
			bool cc6_disable, bool pstate_disable, bool pstate_switch_disable)
{
	struct smu10_hwmgr *data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (separation_time != data->separation_time ||
			cc6_disable != data->cc6_disable ||
			pstate_disable != data->pstate_disable) {
		data->separation_time = separation_time;
		data->cc6_disable = cc6_disable;
		data->pstate_disable = pstate_disable;
		data->cc6_setting_changed = true;
	}
	return 0;
}
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
struct TYPE_2__ {int cc6_setting_changed; int cpu_cc6_disable; int cpu_pstate_disable; scalar_t__ cpu_pstate_separation_time; } ;
struct smu8_hwmgr {TYPE_1__ cc6_settings; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */

__attribute__((used)) static void smu8_reset_cc6_data(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *hw_data = hwmgr->backend;

	hw_data->cc6_settings.cc6_setting_changed = false;
	hw_data->cc6_settings.cpu_pstate_separation_time = 0;
	hw_data->cc6_settings.cpu_cc6_disable = false;
	hw_data->cc6_settings.cpu_pstate_disable = false;
}
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
struct TYPE_3__ {scalar_t__ num_existing_displays; } ;
struct vega10_hwmgr {int /*<<< orphan*/  need_update_dpm_table; TYPE_1__ display_timing; } ;
struct pp_hwmgr {TYPE_2__* display_config; struct vega10_hwmgr* backend; } ;
struct TYPE_4__ {scalar_t__ num_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMTABLE_UPDATE_MCLK ; 

__attribute__((used)) static int vega10_find_dpm_states_clocks_in_dpm_table(struct pp_hwmgr *hwmgr, const void *input)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		data->need_update_dpm_table |= DPMTABLE_UPDATE_MCLK;

	return 0;
}
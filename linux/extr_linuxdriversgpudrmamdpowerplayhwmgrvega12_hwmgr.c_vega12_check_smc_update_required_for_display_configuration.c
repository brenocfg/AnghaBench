#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_existing_displays; scalar_t__ min_clock_in_sr; } ;
struct TYPE_4__ {scalar_t__ gfx_clk_deep_sleep_support; } ;
struct vega12_hwmgr {TYPE_2__ display_timing; TYPE_1__ registry_data; } ;
struct pp_hwmgr {TYPE_3__* display_config; scalar_t__ backend; } ;
struct TYPE_6__ {scalar_t__ num_display; scalar_t__ min_core_set_clock_in_sr; } ;

/* Variables and functions */

__attribute__((used)) static bool
vega12_check_smc_update_required_for_display_configuration(struct pp_hwmgr *hwmgr)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);
	bool is_update_required = false;

	if (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		is_update_required = true;

	if (data->registry_data.gfx_clk_deep_sleep_support) {
		if (data->display_timing.min_clock_in_sr != hwmgr->display_config->min_core_set_clock_in_sr)
			is_update_required = true;
	}

	return is_update_required;
}
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
struct TYPE_3__ {scalar_t__ num_existing_displays; scalar_t__ min_clock_in_sr; } ;
struct vega10_hwmgr {TYPE_1__ display_timing; } ;
struct pp_hwmgr {TYPE_2__* display_config; struct vega10_hwmgr* backend; } ;
struct TYPE_4__ {scalar_t__ num_display; scalar_t__ min_core_set_clock_in_sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
vega10_check_smc_update_required_for_display_configuration(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	bool is_update_required = false;

	if (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		is_update_required = true;

	if (PP_CAP(PHM_PlatformCaps_SclkDeepSleep)) {
		if (data->display_timing.min_clock_in_sr != hwmgr->display_config->min_core_set_clock_in_sr)
			is_update_required = true;
	}

	return is_update_required;
}
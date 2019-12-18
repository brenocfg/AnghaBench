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
struct pp_hwmgr {TYPE_2__* hwmgr_func; } ;
struct amd_pp_display_configuration {int num_path_including_non_display; int /*<<< orphan*/  nb_pstate_switch_disable; int /*<<< orphan*/  cpu_pstate_disable; int /*<<< orphan*/  cpu_cc6_disable; int /*<<< orphan*/  cpu_pstate_separation_time; TYPE_1__* displays; int /*<<< orphan*/  min_dcef_deep_sleep_set_clk; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* store_cc6_data ) (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_active_display_count ) (struct pp_hwmgr*,int) ;int /*<<< orphan*/  (* set_min_deep_sleep_dcefclk ) (struct pp_hwmgr*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ controller_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  stub1 (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  stub3 (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phm_store_dal_configuration_data(struct pp_hwmgr *hwmgr,
		    const struct amd_pp_display_configuration *display_config)
{
	int index = 0;
	int number_of_active_display = 0;

	PHM_FUNC_CHECK(hwmgr);

	if (display_config == NULL)
		return -EINVAL;

	if (NULL != hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk)
		hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk(hwmgr, display_config->min_dcef_deep_sleep_set_clk);

	for (index = 0; index < display_config->num_path_including_non_display; index++) {
		if (display_config->displays[index].controller_id != 0)
			number_of_active_display++;
	}

	if (NULL != hwmgr->hwmgr_func->set_active_display_count)
		hwmgr->hwmgr_func->set_active_display_count(hwmgr, number_of_active_display);

	if (hwmgr->hwmgr_func->store_cc6_data == NULL)
		return -EINVAL;

	/* TODO: pass other display configuration in the future */

	if (hwmgr->hwmgr_func->store_cc6_data)
		hwmgr->hwmgr_func->store_cc6_data(hwmgr,
				display_config->cpu_pstate_separation_time,
				display_config->cpu_cc6_disable,
				display_config->cpu_pstate_disable,
				display_config->nb_pstate_switch_disable);

	return 0;
}
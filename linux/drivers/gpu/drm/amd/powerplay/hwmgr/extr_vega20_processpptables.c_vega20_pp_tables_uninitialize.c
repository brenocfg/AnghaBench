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
struct pp_hwmgr {int /*<<< orphan*/ * pptable; } ;
struct phm_ppt_v3_information {int /*<<< orphan*/ * smc_pptable; int /*<<< orphan*/ * od_settings_min; int /*<<< orphan*/ * od_settings_max; int /*<<< orphan*/ * od_feature_capabilities; int /*<<< orphan*/ * power_saving_clock_min; int /*<<< orphan*/ * power_saving_clock_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega20_pp_tables_uninitialize(struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v3_information *pp_table_info =
			(struct phm_ppt_v3_information *)(hwmgr->pptable);

	kfree(pp_table_info->power_saving_clock_max);
	pp_table_info->power_saving_clock_max = NULL;

	kfree(pp_table_info->power_saving_clock_min);
	pp_table_info->power_saving_clock_min = NULL;

	kfree(pp_table_info->od_feature_capabilities);
	pp_table_info->od_feature_capabilities = NULL;

	kfree(pp_table_info->od_settings_max);
	pp_table_info->od_settings_max = NULL;

	kfree(pp_table_info->od_settings_min);
	pp_table_info->od_settings_min = NULL;

	kfree(pp_table_info->smc_pptable);
	pp_table_info->smc_pptable = NULL;

	kfree(hwmgr->pptable);
	hwmgr->pptable = NULL;

	return 0;
}
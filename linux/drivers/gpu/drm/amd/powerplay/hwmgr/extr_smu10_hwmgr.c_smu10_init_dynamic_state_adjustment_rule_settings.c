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
struct TYPE_4__ {struct phm_clock_voltage_dependency_table* vddc_dep_on_dal_pwrl; } ;
struct pp_hwmgr {TYPE_2__ dyn_state; } ;
struct phm_clock_voltage_dependency_table {int count; TYPE_1__* entries; } ;
struct TYPE_3__ {int v; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_0 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_1 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_2 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_3 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_4 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_5 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_6 ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_7 ; 
 int /*<<< orphan*/  entries ; 
 struct phm_clock_voltage_dependency_table* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  struct_size (struct phm_clock_voltage_dependency_table*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_init_dynamic_state_adjustment_rule_settings(
							struct pp_hwmgr *hwmgr)
{
	struct phm_clock_voltage_dependency_table *table_clk_vlt;

	table_clk_vlt = kzalloc(struct_size(table_clk_vlt, entries, 7),
				GFP_KERNEL);

	if (NULL == table_clk_vlt) {
		pr_err("Can not allocate memory!\n");
		return -ENOMEM;
	}

	table_clk_vlt->count = 8;
	table_clk_vlt->entries[0].clk = PP_DAL_POWERLEVEL_0;
	table_clk_vlt->entries[0].v = 0;
	table_clk_vlt->entries[1].clk = PP_DAL_POWERLEVEL_1;
	table_clk_vlt->entries[1].v = 1;
	table_clk_vlt->entries[2].clk = PP_DAL_POWERLEVEL_2;
	table_clk_vlt->entries[2].v = 2;
	table_clk_vlt->entries[3].clk = PP_DAL_POWERLEVEL_3;
	table_clk_vlt->entries[3].v = 3;
	table_clk_vlt->entries[4].clk = PP_DAL_POWERLEVEL_4;
	table_clk_vlt->entries[4].v = 4;
	table_clk_vlt->entries[5].clk = PP_DAL_POWERLEVEL_5;
	table_clk_vlt->entries[5].v = 5;
	table_clk_vlt->entries[6].clk = PP_DAL_POWERLEVEL_6;
	table_clk_vlt->entries[6].v = 6;
	table_clk_vlt->entries[7].clk = PP_DAL_POWERLEVEL_7;
	table_clk_vlt->entries[7].v = 7;
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = table_clk_vlt;

	return 0;
}
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
struct TYPE_6__ {unsigned long soft_min_clk; unsigned long hard_min_clk; unsigned long soft_max_clk; unsigned long hard_max_clk; } ;
struct smu8_hwmgr {TYPE_3__ sclk_dpm; } ;
struct TYPE_4__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; struct smu8_hwmgr* backend; } ;
struct phm_clock_voltage_dependency_table {unsigned long count; TYPE_2__* entries; } ;
struct TYPE_5__ {unsigned long clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int smu8_get_max_sclk_level (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_init_sclk_limit(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct phm_clock_voltage_dependency_table *table =
					hwmgr->dyn_state.vddc_dependency_on_sclk;
	unsigned long clock = 0, level;

	if (NULL == table || table->count <= 0)
		return -EINVAL;

	data->sclk_dpm.soft_min_clk = table->entries[0].clk;
	data->sclk_dpm.hard_min_clk = table->entries[0].clk;

	level = smu8_get_max_sclk_level(hwmgr) - 1;

	if (level < table->count)
		clock = table->entries[level].clk;
	else
		clock = table->entries[table->count - 1].clk;

	data->sclk_dpm.soft_max_clk = clock;
	data->sclk_dpm.hard_max_clk = clock;

	return 0;
}
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
struct phm_clock_and_voltage_limits {int /*<<< orphan*/  mclk; } ;
struct TYPE_3__ {struct phm_clock_and_voltage_limits max_clock_voltage_on_ac; struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; } ;
struct phm_clock_voltage_dependency_table {unsigned long count; TYPE_2__* entries; } ;
struct amd_pp_simple_clock_info {int /*<<< orphan*/  memory_max_clock; int /*<<< orphan*/  engine_max_clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int smu8_get_max_sclk_level (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu8_get_max_high_clocks(struct pp_hwmgr *hwmgr, struct amd_pp_simple_clock_info *clocks)
{
	struct phm_clock_voltage_dependency_table *table =
					hwmgr->dyn_state.vddc_dependency_on_sclk;
	unsigned long level;
	const struct phm_clock_and_voltage_limits *limits =
			&hwmgr->dyn_state.max_clock_voltage_on_ac;

	if ((NULL == table) || (table->count <= 0) || (clocks == NULL))
		return -EINVAL;

	level = smu8_get_max_sclk_level(hwmgr) - 1;

	if (level < table->count)
		clocks->engine_max_clock = table->entries[level].clk;
	else
		clocks->engine_max_clock = table->entries[table->count - 1].clk;

	clocks->memory_max_clock = limits->mclk;

	return 0;
}
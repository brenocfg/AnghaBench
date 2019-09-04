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
typedef  size_t uint32_t ;
struct phm_clock_and_voltage_limits {scalar_t__ vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct TYPE_4__ {struct phm_clock_and_voltage_limits max_clock_voltage_on_ac; struct phm_clock_voltage_dependency_table* vddc_dep_on_dal_pwrl; } ;
struct pp_hwmgr {TYPE_2__ dyn_state; } ;
struct phm_clock_voltage_dependency_table {size_t count; TYPE_1__* entries; } ;
struct amd_pp_simple_clock_info {int /*<<< orphan*/  level; int /*<<< orphan*/  memory_max_clock; int /*<<< orphan*/  engine_max_clock; } ;
struct TYPE_3__ {scalar_t__ v; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int smu8_get_dal_power_level(struct pp_hwmgr *hwmgr,
		struct amd_pp_simple_clock_info *info)
{
	uint32_t i;
	const struct phm_clock_voltage_dependency_table *table =
			hwmgr->dyn_state.vddc_dep_on_dal_pwrl;
	const struct phm_clock_and_voltage_limits *limits =
			&hwmgr->dyn_state.max_clock_voltage_on_ac;

	info->engine_max_clock = limits->sclk;
	info->memory_max_clock = limits->mclk;

	for (i = table->count - 1; i > 0; i--) {
		if (limits->vddc >= table->entries[i].v) {
			info->level = table->entries[i].clk;
			return 0;
		}
	}
	return -EINVAL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct smu7_power_state {size_t performance_level_count; TYPE_1__* performance_levels; } ;
struct TYPE_10__ {size_t count; TYPE_4__* dpm_levels; } ;
struct TYPE_8__ {size_t count; TYPE_2__* dpm_levels; } ;
struct smu7_dpm_table {TYPE_5__ pcie_speed_table; TYPE_3__ sclk_table; } ;
struct smu7_hwmgr {struct smu7_dpm_table dpm_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {size_t value; } ;
struct TYPE_6__ {size_t engine_clock; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t smu7_get_maximum_link_speed(struct pp_hwmgr *hwmgr,
		const struct smu7_power_state *smu7_ps)
{
	uint32_t i;
	uint32_t sclk, max_sclk = 0;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_dpm_table *dpm_table = &data->dpm_table;

	for (i = 0; i < smu7_ps->performance_level_count; i++) {
		sclk = smu7_ps->performance_levels[i].engine_clock;
		if (max_sclk < sclk)
			max_sclk = sclk;
	}

	for (i = 0; i < dpm_table->sclk_table.count; i++) {
		if (dpm_table->sclk_table.dpm_levels[i].value == max_sclk)
			return (uint16_t) ((i >= dpm_table->pcie_speed_table.count) ?
					dpm_table->pcie_speed_table.dpm_levels
					[dpm_table->pcie_speed_table.count - 1].value :
					dpm_table->pcie_speed_table.dpm_levels[i].value);
	}

	return 0;
}
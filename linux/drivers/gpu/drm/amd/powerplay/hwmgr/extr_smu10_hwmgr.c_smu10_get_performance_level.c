#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {TYPE_2__* vdd_dep_on_fclk; } ;
struct smu10_hwmgr {int /*<<< orphan*/  gfx_max_freq_limit; TYPE_3__ clock_vol_info; int /*<<< orphan*/  gfx_min_freq_limit; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct pp_hw_power_state {int dummy; } ;
struct TYPE_9__ {scalar_t__ nonLocalMemoryWidth; scalar_t__ nonLocalMemoryFreq; int /*<<< orphan*/  coreClock; int /*<<< orphan*/  memory_clock; } ;
struct TYPE_7__ {int count; TYPE_1__* entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  clk; } ;
typedef  int /*<<< orphan*/  PHM_PerformanceLevelDesignation ;
typedef  TYPE_4__ PHM_PerformanceLevel ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int smu10_get_performance_level(struct pp_hwmgr *hwmgr, const struct pp_hw_power_state *state,
				PHM_PerformanceLevelDesignation designation, uint32_t index,
				PHM_PerformanceLevel *level)
{
	struct smu10_hwmgr *data;

	if (level == NULL || hwmgr == NULL || state == NULL)
		return -EINVAL;

	data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (index == 0) {
		level->memory_clock = data->clock_vol_info.vdd_dep_on_fclk->entries[0].clk;
		level->coreClock = data->gfx_min_freq_limit;
	} else {
		level->memory_clock = data->clock_vol_info.vdd_dep_on_fclk->entries[
			data->clock_vol_info.vdd_dep_on_fclk->count - 1].clk;
		level->coreClock = data->gfx_max_freq_limit;
	}

	level->nonLocalMemoryFreq = 0;
	level->nonLocalMemoryWidth = 0;

	return 0;
}
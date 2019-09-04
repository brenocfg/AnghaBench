#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct smu8_power_state {int level; TYPE_2__* levels; } ;
struct TYPE_5__ {int /*<<< orphan*/ * nbp_memory_clock; } ;
struct smu8_hwmgr {scalar_t__ dce_slow_sclk_threshold; TYPE_1__ sys_info; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;
struct pp_hw_power_state {int dummy; } ;
struct TYPE_7__ {scalar_t__ coreClock; int vddc; scalar_t__ nonLocalMemoryWidth; scalar_t__ nonLocalMemoryFreq; int /*<<< orphan*/  memory_clock; } ;
struct TYPE_6__ {scalar_t__ engineClock; int /*<<< orphan*/  vddcIndex; } ;
typedef  scalar_t__ PHM_PerformanceLevelDesignation ;
typedef  TYPE_3__ PHM_PerformanceLevel ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PHM_PerformanceLevelDesignation_PowerContainment ; 
 int SMU8_NUM_NBPMEMORYCLOCK ; 
 struct smu8_power_state* cast_const_smu8_power_state (struct pp_hw_power_state const*) ; 
 int smu8_convert_8Bit_index_to_voltage (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_get_performance_level(struct pp_hwmgr *hwmgr, const struct pp_hw_power_state *state,
				PHM_PerformanceLevelDesignation designation, uint32_t index,
				PHM_PerformanceLevel *level)
{
	const struct smu8_power_state *ps;
	struct smu8_hwmgr *data;
	uint32_t level_index;
	uint32_t i;

	if (level == NULL || hwmgr == NULL || state == NULL)
		return -EINVAL;

	data = hwmgr->backend;
	ps = cast_const_smu8_power_state(state);

	level_index = index > ps->level - 1 ? ps->level - 1 : index;
	level->coreClock = ps->levels[level_index].engineClock;

	if (designation == PHM_PerformanceLevelDesignation_PowerContainment) {
		for (i = 1; i < ps->level; i++) {
			if (ps->levels[i].engineClock > data->dce_slow_sclk_threshold) {
				level->coreClock = ps->levels[i].engineClock;
				break;
			}
		}
	}

	if (level_index == 0)
		level->memory_clock = data->sys_info.nbp_memory_clock[SMU8_NUM_NBPMEMORYCLOCK - 1];
	else
		level->memory_clock = data->sys_info.nbp_memory_clock[0];

	level->vddc = (smu8_convert_8Bit_index_to_voltage(hwmgr, ps->levels[level_index].vddcIndex) + 2) / 4;
	level->nonLocalMemoryFreq = 0;
	level->nonLocalMemoryWidth = 0;

	return 0;
}
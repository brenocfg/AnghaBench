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
typedef  int uint32_t ;
struct smu7_single_dpm_table {int count; TYPE_3__* dpm_levels; } ;
struct smu7_power_state {int performance_level_count; TYPE_2__* performance_levels; } ;
struct TYPE_4__ {struct smu7_single_dpm_table mclk_table; } ;
struct smu7_hwmgr {TYPE_1__ golden_dpm_table; } ;
struct pp_power_state {int /*<<< orphan*/  hardware; } ;
struct pp_hwmgr {struct pp_power_state* request_ps; scalar_t__ backend; } ;
struct TYPE_6__ {int value; } ;
struct TYPE_5__ {int memory_clock; } ;

/* Variables and functions */
 int EINVAL ; 
 struct smu7_power_state* cast_phw_smu7_power_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu7_set_mclk_od(struct pp_hwmgr *hwmgr, uint32_t value)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mclk_table);
	struct pp_power_state  *ps;
	struct smu7_power_state  *smu7_ps;

	if (value > 20)
		value = 20;

	ps = hwmgr->request_ps;

	if (ps == NULL)
		return -EINVAL;

	smu7_ps = cast_phw_smu7_power_state(&ps->hardware);

	smu7_ps->performance_levels[smu7_ps->performance_level_count - 1].memory_clock =
			golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value *
			value / 100 +
			golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value;

	return 0;
}
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
struct smu7_single_dpm_table {int count; TYPE_2__* dpm_levels; } ;
struct TYPE_3__ {struct smu7_single_dpm_table mclk_table; struct smu7_single_dpm_table sclk_table; } ;
struct smu7_hwmgr {TYPE_1__ dpm_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct amd_pp_simple_clock_info {int /*<<< orphan*/  engine_max_clock; int /*<<< orphan*/  memory_max_clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int smu7_get_max_high_clocks(struct pp_hwmgr *hwmgr,
					struct amd_pp_simple_clock_info *clocks)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	struct smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);

	if (clocks == NULL)
		return -EINVAL;

	clocks->memory_max_clock = mclk_table->count > 1 ?
				mclk_table->dpm_levels[mclk_table->count-1].value :
				mclk_table->dpm_levels[0].value;
	clocks->engine_max_clock = sclk_table->count > 1 ?
				sclk_table->dpm_levels[sclk_table->count-1].value :
				sclk_table->dpm_levels[0].value;
	return 0;
}
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
struct vega10_single_dpm_table {int count; TYPE_2__* dpm_levels; } ;
struct TYPE_4__ {struct vega10_single_dpm_table mem_table; } ;
struct TYPE_6__ {struct vega10_single_dpm_table mem_table; } ;
struct vega10_hwmgr {TYPE_1__ golden_dpm_table; TYPE_3__ dpm_table; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct TYPE_5__ {int value; } ;

/* Variables and functions */

__attribute__((used)) static int vega10_get_mclk_od(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct vega10_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	struct vega10_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	int value;

	value = (mclk_table->dpm_levels
			[mclk_table->count - 1].value -
			golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value) *
			100 /
			golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	return value;
}
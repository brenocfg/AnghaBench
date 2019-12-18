#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vega20_single_dpm_table {int count; TYPE_6__* dpm_levels; } ;
struct TYPE_11__ {int count; TYPE_4__* entries; } ;
struct TYPE_7__ {struct vega20_single_dpm_table mem_table; } ;
struct vega20_hwmgr {TYPE_5__ mclk_latency_table; TYPE_2__* smu_features; TYPE_1__ dpm_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct pp_clock_levels_with_latency {int num_levels; TYPE_3__* data; } ;
struct TYPE_12__ {int value; } ;
struct TYPE_10__ {int frequency; int /*<<< orphan*/  latency; } ;
struct TYPE_9__ {int clocks_in_khz; int /*<<< orphan*/  latency_in_us; } ;
struct TYPE_8__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 size_t GNLD_DPM_UCLK ; 
 int MAX_NUM_CLOCKS ; 
 int /*<<< orphan*/  vega20_get_mem_latency (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int vega20_get_memclocks(struct pp_hwmgr *hwmgr,
		struct pp_clock_levels_with_latency *clocks)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	struct vega20_single_dpm_table *dpm_table = &(data->dpm_table.mem_table);
	int i, count;

	if (!data->smu_features[GNLD_DPM_UCLK].enabled)
		return -1;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	clocks->num_levels = data->mclk_latency_table.count = count;

	for (i = 0; i < count; i++) {
		clocks->data[i].clocks_in_khz =
			data->mclk_latency_table.entries[i].frequency =
			dpm_table->dpm_levels[i].value * 1000;
		clocks->data[i].latency_in_us =
			data->mclk_latency_table.entries[i].latency =
			vega20_get_mem_latency(hwmgr, dpm_table->dpm_levels[i].value);
	}

	return 0;
}
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
typedef  int uint32_t ;
struct vega12_single_dpm_table {scalar_t__ count; TYPE_5__* dpm_levels; } ;
struct TYPE_12__ {int count; TYPE_4__* entries; } ;
struct TYPE_8__ {struct vega12_single_dpm_table mem_table; } ;
struct vega12_hwmgr {TYPE_6__ mclk_latency_table; TYPE_2__ dpm_table; TYPE_1__* smu_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct pp_clock_levels_with_latency {int num_levels; TYPE_3__* data; } ;
struct TYPE_11__ {int value; } ;
struct TYPE_10__ {int frequency; int /*<<< orphan*/  latency; } ;
struct TYPE_9__ {int clocks_in_khz; int /*<<< orphan*/  latency_in_us; } ;
struct TYPE_7__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 size_t GNLD_DPM_UCLK ; 
 scalar_t__ MAX_NUM_CLOCKS ; 
 int /*<<< orphan*/  vega12_get_mem_latency (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int vega12_get_memclocks(struct pp_hwmgr *hwmgr,
		struct pp_clock_levels_with_latency *clocks)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);
	uint32_t ucount;
	int i;
	struct vega12_single_dpm_table *dpm_table;
	if (!data->smu_features[GNLD_DPM_UCLK].enabled)
		return -1;

	dpm_table = &(data->dpm_table.mem_table);
	ucount = (dpm_table->count > MAX_NUM_CLOCKS) ?
		MAX_NUM_CLOCKS : dpm_table->count;

	for (i = 0; i < ucount; i++) {
		clocks->data[i].clocks_in_khz = dpm_table->dpm_levels[i].value * 1000;
		data->mclk_latency_table.entries[i].frequency = dpm_table->dpm_levels[i].value * 100;
		clocks->data[i].latency_in_us =
			data->mclk_latency_table.entries[i].latency =
			vega12_get_mem_latency(hwmgr, dpm_table->dpm_levels[i].value);
	}

	clocks->num_levels = data->mclk_latency_table.count = ucount;

	return 0;
}
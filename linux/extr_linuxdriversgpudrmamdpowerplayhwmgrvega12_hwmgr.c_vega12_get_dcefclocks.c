#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vega12_single_dpm_table {scalar_t__ count; TYPE_3__* dpm_levels; } ;
struct TYPE_6__ {struct vega12_single_dpm_table dcef_table; } ;
struct vega12_hwmgr {TYPE_2__ dpm_table; TYPE_1__* smu_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct pp_clock_levels_with_latency {int num_levels; TYPE_4__* data; } ;
struct TYPE_8__ {int clocks_in_khz; scalar_t__ latency_in_us; } ;
struct TYPE_7__ {int value; } ;
struct TYPE_5__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 size_t GNLD_DPM_DCEFCLK ; 
 scalar_t__ MAX_NUM_CLOCKS ; 

__attribute__((used)) static int vega12_get_dcefclocks(struct pp_hwmgr *hwmgr,
		struct pp_clock_levels_with_latency *clocks)
{
	struct vega12_hwmgr *data = (struct vega12_hwmgr *)(hwmgr->backend);
	uint32_t ucount;
	int i;
	struct vega12_single_dpm_table *dpm_table;

	if (!data->smu_features[GNLD_DPM_DCEFCLK].enabled)
		return -1;


	dpm_table = &(data->dpm_table.dcef_table);
	ucount = (dpm_table->count > MAX_NUM_CLOCKS) ?
		MAX_NUM_CLOCKS : dpm_table->count;

	for (i = 0; i < ucount; i++) {
		clocks->data[i].clocks_in_khz =
			dpm_table->dpm_levels[i].value * 1000;

		clocks->data[i].latency_in_us = 0;
	}

	clocks->num_levels = ucount;

	return 0;
}
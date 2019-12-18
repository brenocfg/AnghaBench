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
struct vega20_single_dpm_table {int count; TYPE_1__* dpm_levels; } ;
struct TYPE_6__ {struct vega20_single_dpm_table gfx_table; } ;
struct TYPE_5__ {struct vega20_single_dpm_table gfx_table; } ;
struct vega20_hwmgr {TYPE_3__ golden_dpm_table; TYPE_2__ dpm_table; } ;
struct pp_hwmgr {struct vega20_hwmgr* backend; } ;
struct TYPE_4__ {int value; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static int vega20_get_sclk_od(
		struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data = hwmgr->backend;
	struct vega20_single_dpm_table *sclk_table =
			&(data->dpm_table.gfx_table);
	struct vega20_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.gfx_table);
	int value = sclk_table->dpm_levels[sclk_table->count - 1].value;
	int golden_value = golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value;

	/* od percentage */
	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	return value;
}
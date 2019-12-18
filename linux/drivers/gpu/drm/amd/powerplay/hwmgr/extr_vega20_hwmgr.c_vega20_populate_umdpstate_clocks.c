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
struct vega20_single_dpm_table {size_t count; TYPE_2__* dpm_levels; } ;
struct TYPE_3__ {struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table gfx_table; } ;
struct vega20_hwmgr {TYPE_1__ dpm_table; } ;
struct pp_hwmgr {int pstate_sclk; int pstate_mclk; scalar_t__ backend; } ;
struct TYPE_4__ {int value; } ;

/* Variables and functions */
 size_t VEGA20_UMD_PSTATE_GFXCLK_LEVEL ; 
 size_t VEGA20_UMD_PSTATE_MCLK_LEVEL ; 

__attribute__((used)) static int vega20_populate_umdpstate_clocks(
		struct pp_hwmgr *hwmgr)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	struct vega20_single_dpm_table *gfx_table = &(data->dpm_table.gfx_table);
	struct vega20_single_dpm_table *mem_table = &(data->dpm_table.mem_table);

	hwmgr->pstate_sclk = gfx_table->dpm_levels[0].value;
	hwmgr->pstate_mclk = mem_table->dpm_levels[0].value;

	if (gfx_table->count > VEGA20_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_table->count > VEGA20_UMD_PSTATE_MCLK_LEVEL) {
		hwmgr->pstate_sclk = gfx_table->dpm_levels[VEGA20_UMD_PSTATE_GFXCLK_LEVEL].value;
		hwmgr->pstate_mclk = mem_table->dpm_levels[VEGA20_UMD_PSTATE_MCLK_LEVEL].value;
	}

	hwmgr->pstate_sclk = hwmgr->pstate_sclk * 100;
	hwmgr->pstate_mclk = hwmgr->pstate_mclk * 100;

	return 0;
}
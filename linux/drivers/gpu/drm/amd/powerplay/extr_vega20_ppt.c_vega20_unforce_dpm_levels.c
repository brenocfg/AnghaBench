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
typedef  size_t uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  soft_max_level; int /*<<< orphan*/  soft_min_level; } ;
struct TYPE_9__ {TYPE_3__* dpm_levels; TYPE_2__ dpm_state; } ;
struct vega20_dpm_table {TYPE_4__ soc_table; TYPE_4__ gfx_table; TYPE_4__ mem_table; } ;
struct TYPE_6__ {scalar_t__ dpm_context; } ;
struct smu_context {TYPE_1__ smu_dpm; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 size_t vega20_find_highest_dpm_level (TYPE_4__*) ; 
 size_t vega20_find_lowest_dpm_level (TYPE_4__*) ; 
 int vega20_upload_dpm_level (struct smu_context*,int,int) ; 

__attribute__((used)) static int vega20_unforce_dpm_levels(struct smu_context *smu)
{
	uint32_t soft_min_level, soft_max_level;
	int ret = 0;
	struct vega20_dpm_table *dpm_table =
		(struct vega20_dpm_table *)smu->smu_dpm.dpm_context;

	soft_min_level = vega20_find_lowest_dpm_level(&(dpm_table->gfx_table));
	soft_max_level = vega20_find_highest_dpm_level(&(dpm_table->gfx_table));
	dpm_table->gfx_table.dpm_state.soft_min_level =
		dpm_table->gfx_table.dpm_levels[soft_min_level].value;
	dpm_table->gfx_table.dpm_state.soft_max_level =
		dpm_table->gfx_table.dpm_levels[soft_max_level].value;

	soft_min_level = vega20_find_lowest_dpm_level(&(dpm_table->mem_table));
	soft_max_level = vega20_find_highest_dpm_level(&(dpm_table->mem_table));
	dpm_table->mem_table.dpm_state.soft_min_level =
		dpm_table->gfx_table.dpm_levels[soft_min_level].value;
	dpm_table->mem_table.dpm_state.soft_max_level =
		dpm_table->gfx_table.dpm_levels[soft_max_level].value;

	soft_min_level = vega20_find_lowest_dpm_level(&(dpm_table->soc_table));
	soft_max_level = vega20_find_highest_dpm_level(&(dpm_table->soc_table));
	dpm_table->soc_table.dpm_state.soft_min_level =
		dpm_table->soc_table.dpm_levels[soft_min_level].value;
	dpm_table->soc_table.dpm_state.soft_max_level =
		dpm_table->soc_table.dpm_levels[soft_max_level].value;

	ret = vega20_upload_dpm_level(smu, false, 0xFFFFFFFF);
	if (ret) {
		pr_err("Failed to upload DPM Bootup Levels!");
		return ret;
	}

	ret = vega20_upload_dpm_level(smu, true, 0xFFFFFFFF);
	if (ret) {
		pr_err("Failed to upload DPM Max Levels!");
		return ret;
	}

	return ret;
}
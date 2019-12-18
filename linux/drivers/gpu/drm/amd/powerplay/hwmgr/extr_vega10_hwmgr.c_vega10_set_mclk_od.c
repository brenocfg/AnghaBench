#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vega10_single_dpm_table {int count; TYPE_2__* dpm_levels; } ;
struct vega10_power_state {int performance_level_count; TYPE_3__* performance_levels; } ;
struct TYPE_6__ {struct vega10_single_dpm_table mem_table; } ;
struct vega10_hwmgr {TYPE_1__ golden_dpm_table; } ;
struct pp_power_state {int /*<<< orphan*/  hardware; } ;
struct TYPE_9__ {int memoryClock; } ;
struct TYPE_10__ {TYPE_4__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_5__ platform_descriptor; struct pp_power_state* request_ps; struct vega10_hwmgr* backend; } ;
struct TYPE_8__ {int mem_clock; } ;
struct TYPE_7__ {int value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vega10_power_state* cast_phw_vega10_power_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int vega10_set_mclk_od(struct pp_hwmgr *hwmgr, uint32_t value)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct vega10_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mem_table);
	struct pp_power_state  *ps;
	struct vega10_power_state  *vega10_ps;

	ps = hwmgr->request_ps;

	if (ps == NULL)
		return -EINVAL;

	vega10_ps = cast_phw_vega10_power_state(&ps->hardware);

	vega10_ps->performance_levels
	[vega10_ps->performance_level_count - 1].mem_clock =
			golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value *
			value / 100 +
			golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	if (vega10_ps->performance_levels
			[vega10_ps->performance_level_count - 1].mem_clock >
			hwmgr->platform_descriptor.overdriveLimit.memoryClock) {
		vega10_ps->performance_levels
		[vega10_ps->performance_level_count - 1].mem_clock =
				hwmgr->platform_descriptor.overdriveLimit.memoryClock;
		pr_warn("max mclk supported by vbios is %d\n",
				hwmgr->platform_descriptor.overdriveLimit.memoryClock);
	}

	return 0;
}
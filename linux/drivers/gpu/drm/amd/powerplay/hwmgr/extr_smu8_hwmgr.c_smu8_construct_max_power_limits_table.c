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
typedef  int /*<<< orphan*/  uint16_t ;
struct smu8_sys_info {int /*<<< orphan*/ * nbp_memory_clock; } ;
struct smu8_hwmgr {struct smu8_sys_info sys_info; } ;
struct TYPE_3__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; struct smu8_hwmgr* backend; } ;
struct phm_clock_voltage_dependency_table {int count; TYPE_2__* entries; } ;
struct phm_clock_and_voltage_limits {int /*<<< orphan*/  mclk; int /*<<< orphan*/  vddc; int /*<<< orphan*/  sclk; } ;
struct TYPE_4__ {scalar_t__ v; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu8_convert_8Bit_index_to_voltage (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_construct_max_power_limits_table(struct pp_hwmgr *hwmgr,
			struct phm_clock_and_voltage_limits *table)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct smu8_sys_info *sys_info = &data->sys_info;
	struct phm_clock_voltage_dependency_table *dep_table =
				hwmgr->dyn_state.vddc_dependency_on_sclk;

	if (dep_table->count > 0) {
		table->sclk = dep_table->entries[dep_table->count-1].clk;
		table->vddc = smu8_convert_8Bit_index_to_voltage(hwmgr,
		   (uint16_t)dep_table->entries[dep_table->count-1].v);
	}
	table->mclk = sys_info->nbp_memory_clock[0];
	return 0;
}
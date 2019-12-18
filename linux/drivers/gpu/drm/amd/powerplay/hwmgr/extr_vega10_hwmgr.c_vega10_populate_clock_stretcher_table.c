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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__* CksVidOffset; int /*<<< orphan*/ * CksEnable; } ;
struct TYPE_4__ {TYPE_3__ pp_table; } ;
struct vega10_hwmgr {TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_2__* entries; } ;
struct TYPE_5__ {int cks_voffset; int /*<<< orphan*/  cks_enable; } ;
typedef  TYPE_3__ PPTable_t ;

/* Variables and functions */
 int VOLTAGE_VID_OFFSET_SCALE1 ; 
 int VOLTAGE_VID_OFFSET_SCALE2 ; 

__attribute__((used)) static int vega10_populate_clock_stretcher_table(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_sclk;
	uint32_t i;

	for (i = 0; i < dep_table->count; i++) {
		pp_table->CksEnable[i] = dep_table->entries[i].cks_enable;
		pp_table->CksVidOffset[i] = (uint8_t)(dep_table->entries[i].cks_voffset
				* VOLTAGE_VID_OFFSET_SCALE2 / VOLTAGE_VID_OFFSET_SCALE1);
	}

	return 0;
}
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
typedef  void* uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  vddc_lookup_table; } ;
struct TYPE_8__ {void** SocVid; } ;
struct TYPE_5__ {TYPE_4__ pp_table; } ;
struct vega10_hwmgr {TYPE_2__ odn_dpm_table; TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {scalar_t__ od_enabled; struct phm_ppt_v2_information* pptable; struct vega10_hwmgr* backend; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_voltage_lookup_table* vddc_lookup_table; } ;
struct phm_ppt_v1_voltage_lookup_table {size_t count; TYPE_3__* entries; } ;
struct TYPE_7__ {int /*<<< orphan*/  us_vdd; } ;
typedef  TYPE_4__ PPTable_t ;

/* Variables and functions */
 size_t MAX_REGULAR_DPM_NUMBER ; 
 scalar_t__ convert_to_vid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vega10_populate_vddc_soc_levels(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	struct phm_ppt_v2_information *table_info = hwmgr->pptable;
	struct phm_ppt_v1_voltage_lookup_table *vddc_lookup_table;

	uint8_t soc_vid = 0;
	uint32_t i, max_vddc_level;

	if (hwmgr->od_enabled)
		vddc_lookup_table = (struct phm_ppt_v1_voltage_lookup_table *)&data->odn_dpm_table.vddc_lookup_table;
	else
		vddc_lookup_table = table_info->vddc_lookup_table;

	max_vddc_level = vddc_lookup_table->count;
	for (i = 0; i < max_vddc_level; i++) {
		soc_vid = (uint8_t)convert_to_vid(vddc_lookup_table->entries[i].us_vdd);
		pp_table->SocVid[i] = soc_vid;
	}
	while (i < MAX_REGULAR_DPM_NUMBER) {
		pp_table->SocVid[i] = soc_vid;
		i++;
	}
}
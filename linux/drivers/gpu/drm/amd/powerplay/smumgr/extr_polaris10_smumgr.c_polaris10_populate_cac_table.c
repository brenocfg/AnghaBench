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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {TYPE_1__* entries; } ;
struct smu7_hwmgr {TYPE_2__ vddc_voltage_table; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_voltage_lookup_table {size_t count; TYPE_3__* entries; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_voltage_lookup_table* vddc_lookup_table; } ;
struct SMU74_Discrete_DpmTable {void** BapmVddcVidHiSidd2; void** BapmVddcVidHiSidd; void** BapmVddcVidLoSidd; } ;
struct TYPE_6__ {int /*<<< orphan*/  us_cac_high; int /*<<< orphan*/  us_cac_mid; int /*<<< orphan*/  us_cac_low; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 void* convert_to_vid (int /*<<< orphan*/ ) ; 
 size_t phm_get_voltage_index (struct phm_ppt_v1_voltage_lookup_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int polaris10_populate_cac_table(struct pp_hwmgr *hwmgr,
		struct SMU74_Discrete_DpmTable *table)
{
	uint32_t count;
	uint8_t index;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	struct phm_ppt_v1_voltage_lookup_table *lookup_table =
			table_info->vddc_lookup_table;
	/* tables is already swapped, so in order to use the value from it,
	 * we need to swap it back.
	 * We are populating vddc CAC data to BapmVddc table
	 * in split and merged mode
	 */
	for (count = 0; count < lookup_table->count; count++) {
		index = phm_get_voltage_index(lookup_table,
				data->vddc_voltage_table.entries[count].value);
		table->BapmVddcVidLoSidd[count] = convert_to_vid(lookup_table->entries[index].us_cac_low);
		table->BapmVddcVidHiSidd[count] = convert_to_vid(lookup_table->entries[index].us_cac_mid);
		table->BapmVddcVidHiSidd2[count] = convert_to_vid(lookup_table->entries[index].us_cac_high);
	}

	return 0;
}
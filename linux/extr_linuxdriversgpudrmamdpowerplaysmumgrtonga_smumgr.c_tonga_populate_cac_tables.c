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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_7__ {TYPE_1__* entries; } ;
struct smu7_hwmgr {scalar_t__ vdd_gfx_control; TYPE_2__ vddc_voltage_table; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_voltage_lookup_table {TYPE_3__* entries; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_voltage_lookup_table* vddc_lookup_table; struct phm_ppt_v1_voltage_lookup_table* vddgfx_lookup_table; } ;
struct TYPE_9__ {void** BapmVddGfxVidHiSidd2; void** BapmVddGfxVidHiSidd; void** BapmVddGfxVidLoSidd; void** BapmVddcVidHiSidd2; void** BapmVddcVidHiSidd; void** BapmVddcVidLoSidd; int /*<<< orphan*/  VddGfxLevelCount; int /*<<< orphan*/  VddcLevelCount; } ;
struct TYPE_8__ {int /*<<< orphan*/  us_cac_high; int /*<<< orphan*/  us_cac_mid; int /*<<< orphan*/  us_cac_low; } ;
struct TYPE_6__ {void* value; } ;
typedef  TYPE_4__ SMU72_Discrete_DpmTable ;

/* Variables and functions */
 size_t PP_SMC_TO_HOST_UL (int /*<<< orphan*/ ) ; 
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 
 void* convert_to_vid (int /*<<< orphan*/ ) ; 
 size_t phm_get_voltage_index (struct phm_ppt_v1_voltage_lookup_table*,void*) ; 

__attribute__((used)) static int tonga_populate_cac_tables(struct pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
{
	uint32_t count;
	uint8_t index = 0;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *pptable_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	struct phm_ppt_v1_voltage_lookup_table *vddgfx_lookup_table =
					   pptable_info->vddgfx_lookup_table;
	struct phm_ppt_v1_voltage_lookup_table *vddc_lookup_table =
						pptable_info->vddc_lookup_table;

	/* table is already swapped, so in order to use the value from it
	 * we need to swap it back.
	 */
	uint32_t vddc_level_count = PP_SMC_TO_HOST_UL(table->VddcLevelCount);
	uint32_t vddgfx_level_count = PP_SMC_TO_HOST_UL(table->VddGfxLevelCount);

	for (count = 0; count < vddc_level_count; count++) {
		/* We are populating vddc CAC data to BapmVddc table in split and merged mode */
		index = phm_get_voltage_index(vddc_lookup_table,
			data->vddc_voltage_table.entries[count].value);
		table->BapmVddcVidLoSidd[count] =
			convert_to_vid(vddc_lookup_table->entries[index].us_cac_low);
		table->BapmVddcVidHiSidd[count] =
			convert_to_vid(vddc_lookup_table->entries[index].us_cac_mid);
		table->BapmVddcVidHiSidd2[count] =
			convert_to_vid(vddc_lookup_table->entries[index].us_cac_high);
	}

	if (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) {
		/* We are populating vddgfx CAC data to BapmVddgfx table in split mode */
		for (count = 0; count < vddgfx_level_count; count++) {
			index = phm_get_voltage_index(vddgfx_lookup_table,
				convert_to_vid(vddgfx_lookup_table->entries[index].us_cac_mid));
			table->BapmVddGfxVidHiSidd2[count] =
				convert_to_vid(vddgfx_lookup_table->entries[index].us_cac_high);
		}
	} else {
		for (count = 0; count < vddc_level_count; count++) {
			index = phm_get_voltage_index(vddc_lookup_table,
				data->vddc_voltage_table.entries[count].value);
			table->BapmVddGfxVidLoSidd[count] =
				convert_to_vid(vddc_lookup_table->entries[index].us_cac_low);
			table->BapmVddGfxVidHiSidd[count] =
				convert_to_vid(vddc_lookup_table->entries[index].us_cac_mid);
			table->BapmVddGfxVidHiSidd2[count] =
				convert_to_vid(vddc_lookup_table->entries[index].us_cac_high);
		}
	}

	return 0;
}
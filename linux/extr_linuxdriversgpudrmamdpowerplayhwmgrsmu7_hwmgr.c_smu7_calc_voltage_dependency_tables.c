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
typedef  size_t uint8_t ;
struct smu7_hwmgr {scalar_t__ vdd_gfx_control; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_voltage_lookup_record {scalar_t__ us_vdd; scalar_t__ us_cac_high; scalar_t__ us_cac_mid; scalar_t__ us_cac_low; } ;
struct phm_ppt_v1_information {int /*<<< orphan*/  vddgfx_lookup_table; int /*<<< orphan*/  vddc_lookup_table; TYPE_2__* vdd_dep_on_mclk; TYPE_2__* vdd_dep_on_sclk; } ;
struct TYPE_4__ {size_t count; TYPE_1__* entries; } ;
typedef  TYPE_2__ phm_ppt_v1_clock_voltage_dependency_table ;
struct TYPE_3__ {int vdd_offset; scalar_t__ vddgfx; scalar_t__ vddc; } ;

/* Variables and functions */
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 
 int /*<<< orphan*/  phm_add_voltage (struct pp_hwmgr*,int /*<<< orphan*/ ,struct phm_ppt_v1_voltage_lookup_record*) ; 

__attribute__((used)) static int smu7_calc_voltage_dependency_tables(struct pp_hwmgr *hwmgr)
{
	uint8_t entry_id;
	struct phm_ppt_v1_voltage_lookup_record v_record;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *pptable_info = (struct phm_ppt_v1_information *)(hwmgr->pptable);

	phm_ppt_v1_clock_voltage_dependency_table *sclk_table = pptable_info->vdd_dep_on_sclk;
	phm_ppt_v1_clock_voltage_dependency_table *mclk_table = pptable_info->vdd_dep_on_mclk;

	if (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) {
		for (entry_id = 0; entry_id < sclk_table->count; ++entry_id) {
			if (sclk_table->entries[entry_id].vdd_offset & (1 << 15))
				v_record.us_vdd = sclk_table->entries[entry_id].vddgfx +
					sclk_table->entries[entry_id].vdd_offset - 0xFFFF;
			else
				v_record.us_vdd = sclk_table->entries[entry_id].vddgfx +
					sclk_table->entries[entry_id].vdd_offset;

			sclk_table->entries[entry_id].vddc =
				v_record.us_cac_low = v_record.us_cac_mid =
				v_record.us_cac_high = v_record.us_vdd;

			phm_add_voltage(hwmgr, pptable_info->vddc_lookup_table, &v_record);
		}

		for (entry_id = 0; entry_id < mclk_table->count; ++entry_id) {
			if (mclk_table->entries[entry_id].vdd_offset & (1 << 15))
				v_record.us_vdd = mclk_table->entries[entry_id].vddc +
					mclk_table->entries[entry_id].vdd_offset - 0xFFFF;
			else
				v_record.us_vdd = mclk_table->entries[entry_id].vddc +
					mclk_table->entries[entry_id].vdd_offset;

			mclk_table->entries[entry_id].vddgfx = v_record.us_cac_low =
				v_record.us_cac_mid = v_record.us_cac_high = v_record.us_vdd;
			phm_add_voltage(hwmgr, pptable_info->vddgfx_lookup_table, &v_record);
		}
	}
	return 0;
}
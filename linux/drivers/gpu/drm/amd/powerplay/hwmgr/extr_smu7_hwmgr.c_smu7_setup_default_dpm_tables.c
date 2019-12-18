#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ max_vddc; } ;
struct smu7_hwmgr {TYPE_1__ odn_dpm_table; int /*<<< orphan*/  dpm_table; int /*<<< orphan*/  golden_dpm_table; } ;
struct smu7_dpm_table {int dummy; } ;
struct pp_hwmgr {scalar_t__ pp_table_version; scalar_t__ od_enabled; scalar_t__ backend; } ;

/* Variables and functions */
 scalar_t__ PP_TABLE_V0 ; 
 scalar_t__ PP_TABLE_V1 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smu7_check_dpm_table_updated (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_odn_initial_default_setting (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_reset_dpm_tables (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_setup_default_pcie_table (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_setup_dpm_tables_v0 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_setup_dpm_tables_v1 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_setup_voltage_range_from_vbios (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu7_setup_default_dpm_tables(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	smu7_reset_dpm_tables(hwmgr);

	if (hwmgr->pp_table_version == PP_TABLE_V1)
		smu7_setup_dpm_tables_v1(hwmgr);
	else if (hwmgr->pp_table_version == PP_TABLE_V0)
		smu7_setup_dpm_tables_v0(hwmgr);

	smu7_setup_default_pcie_table(hwmgr);

	/* save a copy of the default DPM table */
	memcpy(&(data->golden_dpm_table), &(data->dpm_table),
			sizeof(struct smu7_dpm_table));

	/* initialize ODN table */
	if (hwmgr->od_enabled) {
		if (data->odn_dpm_table.max_vddc) {
			smu7_check_dpm_table_updated(hwmgr);
		} else {
			smu7_setup_voltage_range_from_vbios(hwmgr);
			smu7_odn_initial_default_setting(hwmgr);
		}
	}
	return 0;
}
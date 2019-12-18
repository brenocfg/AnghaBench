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
struct TYPE_2__ {int /*<<< orphan*/  mvdd_table; int /*<<< orphan*/  vddci_table; int /*<<< orphan*/  vddc_table; int /*<<< orphan*/  mclk_table; int /*<<< orphan*/  sclk_table; } ;
struct smu7_hwmgr {TYPE_1__ dpm_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_REGULAR_DPM_NUMBER ; 
 int /*<<< orphan*/  SMU_MAX_LEVELS_GRAPHICS ; 
 int /*<<< orphan*/  SMU_MAX_LEVELS_MEMORY ; 
 int /*<<< orphan*/  SMU_MAX_LEVELS_MVDD ; 
 int /*<<< orphan*/  SMU_MAX_LEVELS_VDDC ; 
 int /*<<< orphan*/  SMU_MAX_LEVELS_VDDCI ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  phm_reset_single_dpm_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_get_mac_definition (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_reset_dpm_tables(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	memset(&(data->dpm_table), 0x00, sizeof(data->dpm_table));

	phm_reset_single_dpm_table(
			&data->dpm_table.sclk_table,
				smum_get_mac_definition(hwmgr,
					SMU_MAX_LEVELS_GRAPHICS),
					MAX_REGULAR_DPM_NUMBER);
	phm_reset_single_dpm_table(
			&data->dpm_table.mclk_table,
			smum_get_mac_definition(hwmgr,
				SMU_MAX_LEVELS_MEMORY), MAX_REGULAR_DPM_NUMBER);

	phm_reset_single_dpm_table(
			&data->dpm_table.vddc_table,
				smum_get_mac_definition(hwmgr,
					SMU_MAX_LEVELS_VDDC),
					MAX_REGULAR_DPM_NUMBER);
	phm_reset_single_dpm_table(
			&data->dpm_table.vddci_table,
			smum_get_mac_definition(hwmgr,
				SMU_MAX_LEVELS_VDDCI), MAX_REGULAR_DPM_NUMBER);

	phm_reset_single_dpm_table(
			&data->dpm_table.mvdd_table,
				smum_get_mac_definition(hwmgr,
					SMU_MAX_LEVELS_MVDD),
					MAX_REGULAR_DPM_NUMBER);
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct TYPE_10__ {TYPE_1__ max_clock_voltage_on_dc; } ;
struct pp_hwmgr {TYPE_2__ dyn_state; scalar_t__ pptable; } ;
struct TYPE_13__ {int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct phm_ppt_v1_information {int /*<<< orphan*/ * gpio_table; TYPE_5__* vdd_dep_on_sclk; int /*<<< orphan*/  valid_sclk_values; TYPE_5__* vdd_dep_on_mclk; int /*<<< orphan*/  valid_mclk_values; TYPE_8__ max_clock_voltage_on_dc; int /*<<< orphan*/ * pcie_table; int /*<<< orphan*/  cac_dtp_table; int /*<<< orphan*/ * mm_dep_table; } ;
struct TYPE_12__ {scalar_t__ count; } ;
struct TYPE_11__ {scalar_t__ usMMDependencyTableOffset; scalar_t__ usPowerTuneTableOffset; scalar_t__ usMclkDependencyTableOffset; scalar_t__ usSclkDependencyTableOffset; scalar_t__ usHardLimitTableOffset; scalar_t__ usPCIETableOffset; scalar_t__ usGPIOTableOffset; } ;
typedef  int /*<<< orphan*/  PPTable_Generic_SubTable_Header ;
typedef  TYPE_3__ ATOM_Tonga_POWERPLAYTABLE ;
typedef  int /*<<< orphan*/  ATOM_Tonga_MM_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Tonga_MCLK_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Tonga_Hard_Limit_Table ;
typedef  int /*<<< orphan*/  ATOM_Tonga_GPIO_Table ;

/* Variables and functions */
 int get_cac_tdp_table (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int get_gpio_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int get_hard_limits (struct pp_hwmgr*,TYPE_8__*,int /*<<< orphan*/  const*) ; 
 int get_mclk_voltage_dependency_table (struct pp_hwmgr*,TYPE_5__**,int /*<<< orphan*/  const*) ; 
 int get_mm_clock_voltage_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int get_pcie_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int get_sclk_voltage_dependency_table (struct pp_hwmgr*,TYPE_5__**,int /*<<< orphan*/  const*) ; 
 int get_valid_clk (struct pp_hwmgr*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static int init_clock_voltage_dependency(
		struct pp_hwmgr *hwmgr,
		const ATOM_Tonga_POWERPLAYTABLE *powerplay_table
		)
{
	int result = 0;
	struct phm_ppt_v1_information *pp_table_information =
		(struct phm_ppt_v1_information *)(hwmgr->pptable);

	const ATOM_Tonga_MM_Dependency_Table *mm_dependency_table =
		(const ATOM_Tonga_MM_Dependency_Table *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usMMDependencyTableOffset));
	const PPTable_Generic_SubTable_Header *pPowerTuneTable =
		(const PPTable_Generic_SubTable_Header *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usPowerTuneTableOffset));
	const ATOM_Tonga_MCLK_Dependency_Table *mclk_dep_table =
		(const ATOM_Tonga_MCLK_Dependency_Table *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usMclkDependencyTableOffset));
	const PPTable_Generic_SubTable_Header *sclk_dep_table =
		(const PPTable_Generic_SubTable_Header *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usSclkDependencyTableOffset));
	const ATOM_Tonga_Hard_Limit_Table *pHardLimits =
		(const ATOM_Tonga_Hard_Limit_Table *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usHardLimitTableOffset));
	const PPTable_Generic_SubTable_Header *pcie_table =
		(const PPTable_Generic_SubTable_Header *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usPCIETableOffset));
	const ATOM_Tonga_GPIO_Table *gpio_table =
		(const ATOM_Tonga_GPIO_Table *)(((unsigned long) powerplay_table) +
		le16_to_cpu(powerplay_table->usGPIOTableOffset));

	pp_table_information->vdd_dep_on_sclk = NULL;
	pp_table_information->vdd_dep_on_mclk = NULL;
	pp_table_information->mm_dep_table = NULL;
	pp_table_information->pcie_table = NULL;
	pp_table_information->gpio_table = NULL;

	if (powerplay_table->usMMDependencyTableOffset != 0)
		result = get_mm_clock_voltage_table(hwmgr,
		&pp_table_information->mm_dep_table, mm_dependency_table);

	if (result == 0 && powerplay_table->usPowerTuneTableOffset != 0)
		result = get_cac_tdp_table(hwmgr,
		&pp_table_information->cac_dtp_table, pPowerTuneTable);

	if (result == 0 && powerplay_table->usSclkDependencyTableOffset != 0)
		result = get_sclk_voltage_dependency_table(hwmgr,
		&pp_table_information->vdd_dep_on_sclk, sclk_dep_table);

	if (result == 0 && powerplay_table->usMclkDependencyTableOffset != 0)
		result = get_mclk_voltage_dependency_table(hwmgr,
		&pp_table_information->vdd_dep_on_mclk, mclk_dep_table);

	if (result == 0 && powerplay_table->usPCIETableOffset != 0)
		result = get_pcie_table(hwmgr,
		&pp_table_information->pcie_table, pcie_table);

	if (result == 0 && powerplay_table->usHardLimitTableOffset != 0)
		result = get_hard_limits(hwmgr,
		&pp_table_information->max_clock_voltage_on_dc, pHardLimits);

	hwmgr->dyn_state.max_clock_voltage_on_dc.sclk =
		pp_table_information->max_clock_voltage_on_dc.sclk;
	hwmgr->dyn_state.max_clock_voltage_on_dc.mclk =
		pp_table_information->max_clock_voltage_on_dc.mclk;
	hwmgr->dyn_state.max_clock_voltage_on_dc.vddc =
		pp_table_information->max_clock_voltage_on_dc.vddc;
	hwmgr->dyn_state.max_clock_voltage_on_dc.vddci =
		pp_table_information->max_clock_voltage_on_dc.vddci;

	if (result == 0 && (NULL != pp_table_information->vdd_dep_on_mclk)
		&& (0 != pp_table_information->vdd_dep_on_mclk->count))
		result = get_valid_clk(hwmgr, &pp_table_information->valid_mclk_values,
		pp_table_information->vdd_dep_on_mclk);

	if (result == 0 && (NULL != pp_table_information->vdd_dep_on_sclk)
		&& (0 != pp_table_information->vdd_dep_on_sclk->count))
		result = get_valid_clk(hwmgr, &pp_table_information->valid_sclk_values,
		pp_table_information->vdd_dep_on_sclk);

	if (!result && gpio_table)
		result = get_gpio_table(hwmgr, &pp_table_information->gpio_table,
				gpio_table);

	return result;
}
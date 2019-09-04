#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct TYPE_12__ {TYPE_1__ max_clock_voltage_on_dc; } ;
struct pp_hwmgr {TYPE_2__ dyn_state; scalar_t__ pptable; } ;
struct TYPE_15__ {int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct phm_ppt_v2_information {TYPE_5__* vdd_dep_on_mclk; int /*<<< orphan*/  valid_mclk_values; TYPE_5__* vdd_dep_on_dcefclk; int /*<<< orphan*/  valid_dcefclk_values; TYPE_5__* vdd_dep_on_sclk; int /*<<< orphan*/  valid_sclk_values; TYPE_5__* vdd_dep_on_socclk; int /*<<< orphan*/  valid_socclk_values; TYPE_8__ max_clock_voltage_on_dc; int /*<<< orphan*/  pcie_table; int /*<<< orphan*/ * vdd_dep_on_dispclk; int /*<<< orphan*/ * vdd_dep_on_phyclk; int /*<<< orphan*/ * vdd_dep_on_pixclk; int /*<<< orphan*/ * tdp_table; int /*<<< orphan*/ * mm_dep_table; } ;
typedef  int /*<<< orphan*/  Vega10_PPTable_Generic_SubTable_Header ;
struct TYPE_14__ {scalar_t__ count; } ;
struct TYPE_13__ {scalar_t__ usHardLimitTableOffset; scalar_t__ usPCIETableOffset; scalar_t__ usMclkDependencyTableOffset; scalar_t__ usDcefclkDependencyTableOffset; scalar_t__ usDispClkDependencyTableOffset; scalar_t__ usPhyClkDependencyTableOffset; scalar_t__ usPixclkDependencyTableOffset; scalar_t__ usGfxclkDependencyTableOffset; scalar_t__ usSocclkDependencyTableOffset; scalar_t__ usPowerTuneTableOffset; scalar_t__ usMMDependencyTableOffset; } ;
typedef  int /*<<< orphan*/  ATOM_Vega10_SOCCLK_Dependency_Table ;
typedef  TYPE_3__ ATOM_Vega10_POWERPLAYTABLE ;
typedef  int /*<<< orphan*/  ATOM_Vega10_PIXCLK_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_PHYCLK_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_MM_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_MCLK_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_Hard_Limit_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_GFXCLK_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_DISPCLK_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_Vega10_DCEFCLK_Dependency_Table ;

/* Variables and functions */
 int get_dcefclk_voltage_dependency_table (struct pp_hwmgr*,TYPE_5__**,int /*<<< orphan*/  const*) ; 
 int get_gfxclk_voltage_dependency_table (struct pp_hwmgr*,TYPE_5__**,int /*<<< orphan*/  const*) ; 
 int get_hard_limits (struct pp_hwmgr*,TYPE_8__*,int /*<<< orphan*/  const*) ; 
 int get_mclk_voltage_dependency_table (struct pp_hwmgr*,TYPE_5__**,int /*<<< orphan*/  const*) ; 
 int get_mm_clock_voltage_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int get_pcie_table (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int get_pix_clk_voltage_dependency_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int get_socclk_voltage_dependency_table (struct pp_hwmgr*,TYPE_5__**,int /*<<< orphan*/  const*) ; 
 int get_tdp_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int get_valid_clk (struct pp_hwmgr*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static int init_powerplay_extended_tables(
		struct pp_hwmgr *hwmgr,
		const ATOM_Vega10_POWERPLAYTABLE *powerplay_table)
{
	int result = 0;
	struct phm_ppt_v2_information *pp_table_info =
		(struct phm_ppt_v2_information *)(hwmgr->pptable);

	const ATOM_Vega10_MM_Dependency_Table *mm_dependency_table =
			(const ATOM_Vega10_MM_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usMMDependencyTableOffset));
	const Vega10_PPTable_Generic_SubTable_Header *power_tune_table =
			(const Vega10_PPTable_Generic_SubTable_Header *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usPowerTuneTableOffset));
	const ATOM_Vega10_SOCCLK_Dependency_Table *socclk_dep_table =
			(const ATOM_Vega10_SOCCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usSocclkDependencyTableOffset));
	const ATOM_Vega10_GFXCLK_Dependency_Table *gfxclk_dep_table =
			(const ATOM_Vega10_GFXCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usGfxclkDependencyTableOffset));
	const ATOM_Vega10_DCEFCLK_Dependency_Table *dcefclk_dep_table =
			(const ATOM_Vega10_DCEFCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usDcefclkDependencyTableOffset));
	const ATOM_Vega10_MCLK_Dependency_Table *mclk_dep_table =
			(const ATOM_Vega10_MCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usMclkDependencyTableOffset));
	const ATOM_Vega10_Hard_Limit_Table *hard_limits =
			(const ATOM_Vega10_Hard_Limit_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usHardLimitTableOffset));
	const Vega10_PPTable_Generic_SubTable_Header *pcie_table =
			(const Vega10_PPTable_Generic_SubTable_Header *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usPCIETableOffset));
	const ATOM_Vega10_PIXCLK_Dependency_Table *pixclk_dep_table =
			(const ATOM_Vega10_PIXCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usPixclkDependencyTableOffset));
	const ATOM_Vega10_PHYCLK_Dependency_Table *phyclk_dep_table =
			(const ATOM_Vega10_PHYCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usPhyClkDependencyTableOffset));
	const ATOM_Vega10_DISPCLK_Dependency_Table *dispclk_dep_table =
			(const ATOM_Vega10_DISPCLK_Dependency_Table *)
			(((unsigned long) powerplay_table) +
			le16_to_cpu(powerplay_table->usDispClkDependencyTableOffset));

	pp_table_info->vdd_dep_on_socclk = NULL;
	pp_table_info->vdd_dep_on_sclk = NULL;
	pp_table_info->vdd_dep_on_mclk = NULL;
	pp_table_info->vdd_dep_on_dcefclk = NULL;
	pp_table_info->mm_dep_table = NULL;
	pp_table_info->tdp_table = NULL;
	pp_table_info->vdd_dep_on_pixclk = NULL;
	pp_table_info->vdd_dep_on_phyclk = NULL;
	pp_table_info->vdd_dep_on_dispclk = NULL;

	if (powerplay_table->usMMDependencyTableOffset)
		result = get_mm_clock_voltage_table(hwmgr,
				&pp_table_info->mm_dep_table,
				mm_dependency_table);

	if (!result && powerplay_table->usPowerTuneTableOffset)
		result = get_tdp_table(hwmgr,
				&pp_table_info->tdp_table,
				power_tune_table);

	if (!result && powerplay_table->usSocclkDependencyTableOffset)
		result = get_socclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_socclk,
				socclk_dep_table);

	if (!result && powerplay_table->usGfxclkDependencyTableOffset)
		result = get_gfxclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_sclk,
				gfxclk_dep_table);

	if (!result && powerplay_table->usPixclkDependencyTableOffset)
		result = get_pix_clk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_pixclk,
				(const ATOM_Vega10_PIXCLK_Dependency_Table*)
				pixclk_dep_table);

	if (!result && powerplay_table->usPhyClkDependencyTableOffset)
		result = get_pix_clk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_phyclk,
				(const ATOM_Vega10_PIXCLK_Dependency_Table *)
				phyclk_dep_table);

	if (!result && powerplay_table->usDispClkDependencyTableOffset)
		result = get_pix_clk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_dispclk,
				(const ATOM_Vega10_PIXCLK_Dependency_Table *)
				dispclk_dep_table);

	if (!result && powerplay_table->usDcefclkDependencyTableOffset)
		result = get_dcefclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_dcefclk,
				dcefclk_dep_table);

	if (!result && powerplay_table->usMclkDependencyTableOffset)
		result = get_mclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_mclk,
				mclk_dep_table);

	if (!result && powerplay_table->usPCIETableOffset)
		result = get_pcie_table(hwmgr,
				&pp_table_info->pcie_table,
				pcie_table);

	if (!result && powerplay_table->usHardLimitTableOffset)
		result = get_hard_limits(hwmgr,
				&pp_table_info->max_clock_voltage_on_dc,
				hard_limits);

	hwmgr->dyn_state.max_clock_voltage_on_dc.sclk =
			pp_table_info->max_clock_voltage_on_dc.sclk;
	hwmgr->dyn_state.max_clock_voltage_on_dc.mclk =
			pp_table_info->max_clock_voltage_on_dc.mclk;
	hwmgr->dyn_state.max_clock_voltage_on_dc.vddc =
			pp_table_info->max_clock_voltage_on_dc.vddc;
	hwmgr->dyn_state.max_clock_voltage_on_dc.vddci =
			pp_table_info->max_clock_voltage_on_dc.vddci;

	if (!result &&
		pp_table_info->vdd_dep_on_socclk &&
		pp_table_info->vdd_dep_on_socclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_socclk_values,
				pp_table_info->vdd_dep_on_socclk);

	if (!result &&
		pp_table_info->vdd_dep_on_sclk &&
		pp_table_info->vdd_dep_on_sclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_sclk_values,
				pp_table_info->vdd_dep_on_sclk);

	if (!result &&
		pp_table_info->vdd_dep_on_dcefclk &&
		pp_table_info->vdd_dep_on_dcefclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_dcefclk_values,
				pp_table_info->vdd_dep_on_dcefclk);

	if (!result &&
		pp_table_info->vdd_dep_on_mclk &&
		pp_table_info->vdd_dep_on_mclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_mclk_values,
				pp_table_info->vdd_dep_on_mclk);

	return result;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct vega10_single_dpm_table {int count; TYPE_12__* dpm_levels; } ;
struct vega10_pcie_table {int count; int* pcie_gen; } ;
struct vega10_odn_clock_voltage_dependency_table {int count; TYPE_1__* entries; } ;
struct TYPE_24__ {int min_vddc; int max_vddc; struct vega10_odn_clock_voltage_dependency_table vdd_dep_on_mclk; struct vega10_odn_clock_voltage_dependency_table vdd_dep_on_sclk; } ;
struct TYPE_20__ {TYPE_4__* dpm_levels; } ;
struct TYPE_18__ {TYPE_2__* dpm_levels; } ;
struct TYPE_21__ {TYPE_5__ mem_table; TYPE_3__ gfx_table; } ;
struct TYPE_14__ {int /*<<< orphan*/  dcefclk_dpm_key_disabled; int /*<<< orphan*/  socclk_dpm_key_disabled; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct TYPE_13__ {struct vega10_pcie_table pcie_table; struct vega10_single_dpm_table dcef_table; struct vega10_single_dpm_table soc_table; struct vega10_single_dpm_table mem_table; struct vega10_single_dpm_table gfx_table; } ;
struct vega10_hwmgr {TYPE_9__ odn_dpm_table; TYPE_6__ golden_dpm_table; TYPE_11__ registry_data; TYPE_10__ dpm_table; } ;
struct TYPE_22__ {int engineClock; int memoryClock; } ;
struct TYPE_23__ {TYPE_7__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_8__ platform_descriptor; int /*<<< orphan*/  od_enabled; struct vega10_hwmgr* backend; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;
struct TYPE_19__ {int value; } ;
struct TYPE_17__ {int value; } ;
struct TYPE_16__ {int clk; int vddc; } ;
struct TYPE_15__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_DCEFCLK ; 
#define  OD_MCLK 135 
#define  OD_RANGE 134 
#define  OD_SCLK 133 
 int /*<<< orphan*/  PPSMC_MSG_GetClockFreqMHz ; 
 int /*<<< orphan*/  PPSMC_MSG_GetCurrentGfxclkIndex ; 
 int /*<<< orphan*/  PPSMC_MSG_GetCurrentLinkIndex ; 
 int /*<<< orphan*/  PPSMC_MSG_GetCurrentSocclkIndex ; 
 int /*<<< orphan*/  PPSMC_MSG_GetCurrentUclkIndex ; 
#define  PP_DCEFCLK 132 
#define  PP_MCLK 131 
#define  PP_PCIE 130 
#define  PP_SCLK 129 
#define  PP_SOCCLK 128 
 int smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int vega10_print_clock_levels(struct pp_hwmgr *hwmgr,
		enum pp_clock_type type, char *buf)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct vega10_single_dpm_table *sclk_table = &(data->dpm_table.gfx_table);
	struct vega10_single_dpm_table *mclk_table = &(data->dpm_table.mem_table);
	struct vega10_single_dpm_table *soc_table = &(data->dpm_table.soc_table);
	struct vega10_single_dpm_table *dcef_table = &(data->dpm_table.dcef_table);
	struct vega10_pcie_table *pcie_table = &(data->dpm_table.pcie_table);
	struct vega10_odn_clock_voltage_dependency_table *podn_vdd_dep = NULL;

	int i, now, size = 0;

	switch (type) {
	case PP_SCLK:
		if (data->registry_data.sclk_dpm_key_disabled)
			break;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentGfxclkIndex);
		now = smum_get_argument(hwmgr);

		for (i = 0; i < sclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_MCLK:
		if (data->registry_data.mclk_dpm_key_disabled)
			break;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentUclkIndex);
		now = smum_get_argument(hwmgr);

		for (i = 0; i < mclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, mclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_SOCCLK:
		if (data->registry_data.socclk_dpm_key_disabled)
			break;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentSocclkIndex);
		now = smum_get_argument(hwmgr);

		for (i = 0; i < soc_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, soc_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_DCEFCLK:
		if (data->registry_data.dcefclk_dpm_key_disabled)
			break;

		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_GetClockFreqMHz, CLK_DCEFCLK);
		now = smum_get_argument(hwmgr);

		for (i = 0; i < dcef_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, dcef_table->dpm_levels[i].value / 100,
					(dcef_table->dpm_levels[i].value / 100 == now) ?
					"*" : "");
		break;
	case PP_PCIE:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentLinkIndex);
		now = smum_get_argument(hwmgr);

		for (i = 0; i < pcie_table->count; i++)
			size += sprintf(buf + size, "%d: %s %s\n", i,
					(pcie_table->pcie_gen[i] == 0) ? "2.5GT/s, x1" :
					(pcie_table->pcie_gen[i] == 1) ? "5.0GT/s, x16" :
					(pcie_table->pcie_gen[i] == 2) ? "8.0GT/s, x16" : "",
					(i == now) ? "*" : "");
		break;
	case OD_SCLK:
		if (hwmgr->od_enabled) {
			size = sprintf(buf, "%s:\n", "OD_SCLK");
			podn_vdd_dep = &data->odn_dpm_table.vdd_dep_on_sclk;
			for (i = 0; i < podn_vdd_dep->count; i++)
				size += sprintf(buf + size, "%d: %10uMhz %10umV\n",
					i, podn_vdd_dep->entries[i].clk / 100,
						podn_vdd_dep->entries[i].vddc);
		}
		break;
	case OD_MCLK:
		if (hwmgr->od_enabled) {
			size = sprintf(buf, "%s:\n", "OD_MCLK");
			podn_vdd_dep = &data->odn_dpm_table.vdd_dep_on_mclk;
			for (i = 0; i < podn_vdd_dep->count; i++)
				size += sprintf(buf + size, "%d: %10uMhz %10umV\n",
					i, podn_vdd_dep->entries[i].clk/100,
						podn_vdd_dep->entries[i].vddc);
		}
		break;
	case OD_RANGE:
		if (hwmgr->od_enabled) {
			size = sprintf(buf, "%s:\n", "OD_RANGE");
			size += sprintf(buf + size, "SCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.gfx_table.dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.engineClock/100);
			size += sprintf(buf + size, "MCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.mem_table.dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.memoryClock/100);
			size += sprintf(buf + size, "VDDC: %7umV %11umV\n",
				data->odn_dpm_table.min_vddc,
				data->odn_dpm_table.max_vddc);
		}
		break;
	default:
		break;
	}
	return size;
}
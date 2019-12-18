#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct smu7_single_dpm_table {int count; TYPE_10__* dpm_levels; } ;
struct phm_odn_clock_levels {int num_of_pl; TYPE_1__* entries; } ;
struct smu7_odn_dpm_table {int min_vddc; int max_vddc; struct phm_odn_clock_levels odn_memory_clock_dpm_levels; struct phm_odn_clock_levels odn_core_clock_dpm_levels; } ;
struct TYPE_16__ {TYPE_4__* dpm_levels; } ;
struct TYPE_14__ {TYPE_2__* dpm_levels; } ;
struct TYPE_17__ {TYPE_5__ mclk_table; TYPE_3__ sclk_table; } ;
struct TYPE_20__ {struct smu7_single_dpm_table pcie_speed_table; struct smu7_single_dpm_table mclk_table; struct smu7_single_dpm_table sclk_table; } ;
struct smu7_hwmgr {struct smu7_odn_dpm_table odn_dpm_table; TYPE_6__ golden_dpm_table; TYPE_9__ dpm_table; } ;
struct TYPE_18__ {int engineClock; int memoryClock; } ;
struct TYPE_19__ {TYPE_7__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_8__ platform_descriptor; int /*<<< orphan*/  od_enabled; int /*<<< orphan*/  device; scalar_t__ backend; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;
struct TYPE_15__ {int value; } ;
struct TYPE_13__ {int value; } ;
struct TYPE_12__ {int clock; int vddc; } ;
struct TYPE_11__ {int value; } ;

/* Variables and functions */
#define  OD_MCLK 133 
#define  OD_RANGE 132 
#define  OD_SCLK 131 
 int /*<<< orphan*/  PPSMC_MSG_API_GetMclkFrequency ; 
 int /*<<< orphan*/  PPSMC_MSG_API_GetSclkFrequency ; 
#define  PP_MCLK 130 
#define  PP_PCIE 129 
#define  PP_SCLK 128 
 int cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMC_MSG_ARG_0 ; 
 int smu7_get_current_pcie_speed (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int smu7_print_clock_levels(struct pp_hwmgr *hwmgr,
		enum pp_clock_type type, char *buf)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	struct smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);
	struct smu7_single_dpm_table *pcie_table = &(data->dpm_table.pcie_speed_table);
	struct smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	struct phm_odn_clock_levels *odn_sclk_table = &(odn_table->odn_core_clock_dpm_levels);
	struct phm_odn_clock_levels *odn_mclk_table = &(odn_table->odn_memory_clock_dpm_levels);
	int i, now, size = 0;
	uint32_t clock, pcie_speed;

	switch (type) {
	case PP_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetSclkFrequency);
		clock = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);

		for (i = 0; i < sclk_table->count; i++) {
			if (clock > sclk_table->dpm_levels[i].value)
				continue;
			break;
		}
		now = i;

		for (i = 0; i < sclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetMclkFrequency);
		clock = cgs_read_register(hwmgr->device, mmSMC_MSG_ARG_0);

		for (i = 0; i < mclk_table->count; i++) {
			if (clock > mclk_table->dpm_levels[i].value)
				continue;
			break;
		}
		now = i;

		for (i = 0; i < mclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, mclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_PCIE:
		pcie_speed = smu7_get_current_pcie_speed(hwmgr);
		for (i = 0; i < pcie_table->count; i++) {
			if (pcie_speed != pcie_table->dpm_levels[i].value)
				continue;
			break;
		}
		now = i;

		for (i = 0; i < pcie_table->count; i++)
			size += sprintf(buf + size, "%d: %s %s\n", i,
					(pcie_table->dpm_levels[i].value == 0) ? "2.5GT/s, x8" :
					(pcie_table->dpm_levels[i].value == 1) ? "5.0GT/s, x16" :
					(pcie_table->dpm_levels[i].value == 2) ? "8.0GT/s, x16" : "",
					(i == now) ? "*" : "");
		break;
	case OD_SCLK:
		if (hwmgr->od_enabled) {
			size = sprintf(buf, "%s:\n", "OD_SCLK");
			for (i = 0; i < odn_sclk_table->num_of_pl; i++)
				size += sprintf(buf + size, "%d: %10uMHz %10umV\n",
					i, odn_sclk_table->entries[i].clock/100,
					odn_sclk_table->entries[i].vddc);
		}
		break;
	case OD_MCLK:
		if (hwmgr->od_enabled) {
			size = sprintf(buf, "%s:\n", "OD_MCLK");
			for (i = 0; i < odn_mclk_table->num_of_pl; i++)
				size += sprintf(buf + size, "%d: %10uMHz %10umV\n",
					i, odn_mclk_table->entries[i].clock/100,
					odn_mclk_table->entries[i].vddc);
		}
		break;
	case OD_RANGE:
		if (hwmgr->od_enabled) {
			size = sprintf(buf, "%s:\n", "OD_RANGE");
			size += sprintf(buf + size, "SCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.sclk_table.dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.engineClock/100);
			size += sprintf(buf + size, "MCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.mclk_table.dpm_levels[0].value/100,
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
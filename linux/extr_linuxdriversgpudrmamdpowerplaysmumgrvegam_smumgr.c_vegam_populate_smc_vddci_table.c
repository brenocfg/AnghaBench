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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {scalar_t__ count; int /*<<< orphan*/  mask_low; TYPE_3__* entries; } ;
struct smu7_hwmgr {scalar_t__ vddci_control; TYPE_4__ vddci_voltage_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_6__ {TYPE_1__* Pattern; } ;
struct SMU75_Discrete_DpmTable {int /*<<< orphan*/  SmioMask1; int /*<<< orphan*/ * Smio; TYPE_2__ SmioTable1; } ;
struct TYPE_7__ {int value; int /*<<< orphan*/  smio_low; } ;
struct TYPE_5__ {scalar_t__ Smio; int /*<<< orphan*/  Voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_HOST_TO_SMC_US (int) ; 
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_GPIO ; 
 scalar_t__ SMU_MAX_SMIO_LEVELS ; 
 int VOLTAGE_SCALE ; 

__attribute__((used)) static int vegam_populate_smc_vddci_table(struct pp_hwmgr *hwmgr,
					struct SMU75_Discrete_DpmTable *table)
{
	uint32_t count, level;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	count = data->vddci_voltage_table.count;

	if (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) {
		if (count > SMU_MAX_SMIO_LEVELS)
			count = SMU_MAX_SMIO_LEVELS;
		for (level = 0; level < count; ++level) {
			table->SmioTable1.Pattern[level].Voltage = PP_HOST_TO_SMC_US(
					data->vddci_voltage_table.entries[level].value * VOLTAGE_SCALE);
			table->SmioTable1.Pattern[level].Smio = (uint8_t) level;

			table->Smio[level] |= data->vddci_voltage_table.entries[level].smio_low;
		}
	}

	table->SmioMask1 = data->vddci_voltage_table.mask_low;

	return 0;
}
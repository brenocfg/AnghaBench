#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_10__ {size_t count; int /*<<< orphan*/  mask_low; TYPE_3__* entries; } ;
struct smu7_hwmgr {scalar_t__ vddci_control; TYPE_4__ vddci_voltage_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct TYPE_8__ {TYPE_1__* Pattern; } ;
struct TYPE_11__ {size_t VddciLevelCount; int /*<<< orphan*/  SmioMask1; void** VddciTable; int /*<<< orphan*/ * Smio; TYPE_2__ SmioTable1; } ;
struct TYPE_9__ {int value; int /*<<< orphan*/  smio_low; } ;
struct TYPE_7__ {scalar_t__ Smio; void* Voltage; } ;
typedef  TYPE_5__ SMU72_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_UL (size_t) ; 
 void* PP_HOST_TO_SMC_US (int) ; 
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_GPIO ; 
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 
 int VOLTAGE_SCALE ; 

__attribute__((used)) static int tonga_populate_smc_vdd_ci_table(struct pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	uint32_t count;

	table->VddciLevelCount = data->vddci_voltage_table.count;
	for (count = 0; count < table->VddciLevelCount; count++) {
		if (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control) {
			table->VddciTable[count] =
				PP_HOST_TO_SMC_US(data->vddci_voltage_table.entries[count].value * VOLTAGE_SCALE);
		} else if (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) {
			table->SmioTable1.Pattern[count].Voltage =
				PP_HOST_TO_SMC_US(data->vddci_voltage_table.entries[count].value * VOLTAGE_SCALE);
			/* Index into DpmTable.Smio. Drive bits from Smio entry to get this voltage level. */
			table->SmioTable1.Pattern[count].Smio =
				(uint8_t) count;
			table->Smio[count] |=
				data->vddci_voltage_table.entries[count].smio_low;
			table->VddciTable[count] =
				PP_HOST_TO_SMC_US(data->vddci_voltage_table.entries[count].value * VOLTAGE_SCALE);
		}
	}

	table->SmioMask1 = data->vddci_voltage_table.mask_low;
	CONVERT_FROM_HOST_TO_SMC_UL(table->VddciLevelCount);

	return 0;
}
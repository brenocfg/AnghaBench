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
struct smu_table_context {int /*<<< orphan*/  TDPODLimit; int /*<<< orphan*/  thermal_controller_type; int /*<<< orphan*/  driver_pptable; TYPE_2__* power_play_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ODSettingsMax; } ;
struct TYPE_4__ {TYPE_1__ OverDrive8Table; int /*<<< orphan*/  ucThermalControllerType; int /*<<< orphan*/  smcPPTable; } ;
typedef  int /*<<< orphan*/  PPTable_t ;
typedef  TYPE_2__ ATOM_Vega20_POWERPLAYTABLE ;

/* Variables and functions */
 size_t ATOM_VEGA20_ODSETTING_POWERPERCENTAGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vega20_store_powerplay_table(struct smu_context *smu)
{
	ATOM_Vega20_POWERPLAYTABLE *powerplay_table = NULL;
	struct smu_table_context *table_context = &smu->smu_table;

	if (!table_context->power_play_table)
		return -EINVAL;

	powerplay_table = table_context->power_play_table;

	memcpy(table_context->driver_pptable, &powerplay_table->smcPPTable,
	       sizeof(PPTable_t));

	table_context->thermal_controller_type = powerplay_table->ucThermalControllerType;
	table_context->TDPODLimit = le32_to_cpu(powerplay_table->OverDrive8Table.ODSettingsMax[ATOM_VEGA20_ODSETTING_POWERPERCENTAGE]);

	return 0;
}
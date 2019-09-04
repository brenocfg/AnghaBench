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
struct TYPE_2__ {scalar_t__* LPMLTemperatureScaler; } ;
struct tonga_smumgr {TYPE_1__ power_tune_table; } ;
struct pp_hwmgr {scalar_t__ smu_backend; } ;

/* Variables and functions */

__attribute__((used)) static int tonga_populate_temperature_scaler(struct pp_hwmgr *hwmgr)
{
	int i;
	struct tonga_smumgr *smu_data =
				(struct tonga_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	for (i = 0; i < 16; i++)
		smu_data->power_tune_table.LPMLTemperatureScaler[i] = 0;

	return 0;
}
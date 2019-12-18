#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pp_hwmgr {int smu_version; } ;
struct TYPE_3__ {int AverageSocketPower; int CurrSocketPower; } ;
typedef  TYPE_1__ SmuMetrics_t ;

/* Variables and functions */
 int vega20_get_metrics_table (struct pp_hwmgr*,TYPE_1__*) ; 

__attribute__((used)) static int vega20_get_gpu_power(struct pp_hwmgr *hwmgr,
		uint32_t *query)
{
	int ret = 0;
	SmuMetrics_t metrics_table;

	ret = vega20_get_metrics_table(hwmgr, &metrics_table);
	if (ret)
		return ret;

	/* For the 40.46 release, they changed the value name */
	if (hwmgr->smu_version == 0x282e00)
		*query = metrics_table.AverageSocketPower << 8;
	else
		*query = metrics_table.CurrSocketPower << 8;

	return ret;
}
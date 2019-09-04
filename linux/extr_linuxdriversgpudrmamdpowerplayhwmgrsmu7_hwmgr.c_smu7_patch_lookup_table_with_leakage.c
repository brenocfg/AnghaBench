#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct smu7_leakage_voltage {int dummy; } ;
struct pp_hwmgr {int dummy; } ;
struct TYPE_5__ {size_t count; TYPE_1__* entries; } ;
typedef  TYPE_2__ phm_ppt_v1_voltage_lookup_table ;
struct TYPE_4__ {int /*<<< orphan*/  us_vdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  smu7_patch_ppt_v1_with_vdd_leakage (struct pp_hwmgr*,int /*<<< orphan*/ *,struct smu7_leakage_voltage*) ; 

__attribute__((used)) static int smu7_patch_lookup_table_with_leakage(struct pp_hwmgr *hwmgr,
		phm_ppt_v1_voltage_lookup_table *lookup_table,
		struct smu7_leakage_voltage *leakage_table)
{
	uint32_t i;

	for (i = 0; i < lookup_table->count; i++)
		smu7_patch_ppt_v1_with_vdd_leakage(hwmgr,
				&lookup_table->entries[i].us_vdd, leakage_table);

	return 0;
}
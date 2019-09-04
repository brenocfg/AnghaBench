#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {int dummy; } ;
struct phm_vce_clock_voltage_dependency_table {int count; TYPE_2__* entries; } ;
struct TYPE_10__ {TYPE_4__* entries; } ;
typedef  TYPE_3__ VCEClockInfoArray ;
struct TYPE_11__ {int /*<<< orphan*/  usECClkLow; scalar_t__ ucECClkHigh; int /*<<< orphan*/  usEVClkLow; scalar_t__ ucEVClkHigh; } ;
typedef  TYPE_4__ VCEClockInfo ;
struct TYPE_12__ {int numEntries; TYPE_1__* entries; } ;
struct TYPE_9__ {unsigned long v; unsigned long evclk; unsigned long ecclk; } ;
struct TYPE_8__ {size_t ucVCEClockInfoIndex; int /*<<< orphan*/  usVoltage; } ;
typedef  TYPE_5__ ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct phm_vce_clock_voltage_dependency_table* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vce_clock_voltage_limit_table(struct pp_hwmgr *hwmgr,
		struct phm_vce_clock_voltage_dependency_table **ptable,
		const ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *table,
		const VCEClockInfoArray    *array)
{
	unsigned long table_size, i;
	struct phm_vce_clock_voltage_dependency_table *vce_table = NULL;

	table_size = sizeof(unsigned long) +
			sizeof(struct phm_vce_clock_voltage_dependency_table)
			* table->numEntries;

	vce_table = kzalloc(table_size, GFP_KERNEL);
	if (NULL == vce_table)
		return -ENOMEM;

	vce_table->count = table->numEntries;
	for (i = 0; i < table->numEntries; i++) {
		const VCEClockInfo *entry = &array->entries[table->entries[i].ucVCEClockInfoIndex];

		vce_table->entries[i].v = (unsigned long)le16_to_cpu(table->entries[i].usVoltage);
		vce_table->entries[i].evclk = ((unsigned long)entry->ucEVClkHigh << 16)
					| le16_to_cpu(entry->usEVClkLow);
		vce_table->entries[i].ecclk = ((unsigned long)entry->ucECClkHigh << 16)
					| le16_to_cpu(entry->usECClkLow);
	}

	*ptable = vce_table;

	return 0;
}
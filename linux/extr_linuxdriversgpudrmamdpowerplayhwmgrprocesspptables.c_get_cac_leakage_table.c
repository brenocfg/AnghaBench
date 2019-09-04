#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; } ;
struct phm_cac_leakage_table {unsigned long count; TYPE_2__* entries; } ;
typedef  unsigned long ULONG ;
struct TYPE_9__ {int ucNumEntries; TYPE_3__* entries; } ;
struct TYPE_8__ {int /*<<< orphan*/  ulLeakageValue; int /*<<< orphan*/  usVddc; int /*<<< orphan*/  usVddc3; int /*<<< orphan*/  usVddc2; int /*<<< orphan*/  usVddc1; } ;
struct TYPE_7__ {int /*<<< orphan*/  Leakage; void* Vddc; void* Vddc3; void* Vddc2; void* Vddc1; } ;
typedef  TYPE_4__ ATOM_PPLIB_CAC_Leakage_Table ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_EVV ; 
 struct phm_cac_leakage_table* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_cac_leakage_table(struct pp_hwmgr *hwmgr,
				 struct phm_cac_leakage_table **ptable,
				const ATOM_PPLIB_CAC_Leakage_Table *table)
{
	struct phm_cac_leakage_table  *cac_leakage_table;
	unsigned long            table_size, i;

	if (hwmgr == NULL || table == NULL || ptable == NULL)
		return -EINVAL;

	table_size = sizeof(ULONG) +
		(sizeof(struct phm_cac_leakage_table) * table->ucNumEntries);

	cac_leakage_table = kzalloc(table_size, GFP_KERNEL);

	if (cac_leakage_table == NULL)
		return -ENOMEM;

	cac_leakage_table->count = (ULONG)table->ucNumEntries;

	for (i = 0; i < cac_leakage_table->count; i++) {
		if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_EVV)) {
			cac_leakage_table->entries[i].Vddc1 = le16_to_cpu(table->entries[i].usVddc1);
			cac_leakage_table->entries[i].Vddc2 = le16_to_cpu(table->entries[i].usVddc2);
			cac_leakage_table->entries[i].Vddc3 = le16_to_cpu(table->entries[i].usVddc3);
		} else {
			cac_leakage_table->entries[i].Vddc    = le16_to_cpu(table->entries[i].usVddc);
			cac_leakage_table->entries[i].Leakage = le32_to_cpu(table->entries[i].ulLeakageValue);
		}
	}

	*ptable = cac_leakage_table;

	return 0;
}
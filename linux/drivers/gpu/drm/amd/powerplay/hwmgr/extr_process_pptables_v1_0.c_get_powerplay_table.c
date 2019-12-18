#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pp_hwmgr {int /*<<< orphan*/  soft_pp_table_size; void* soft_pp_table; int /*<<< orphan*/  adev; } ;
typedef  int /*<<< orphan*/  ATOM_Tonga_POWERPLAYTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const void *get_powerplay_table(struct pp_hwmgr *hwmgr)
{
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);

	u16 size;
	u8 frev, crev;
	void *table_address = (void *)hwmgr->soft_pp_table;

	if (!table_address) {
		table_address = (ATOM_Tonga_POWERPLAYTABLE *)
				smu_atom_get_data_table(hwmgr->adev,
						index, &size, &frev, &crev);
		hwmgr->soft_pp_table = table_address;	/*Cache the result in RAM.*/
		hwmgr->soft_pp_table_size = size;
	}

	return table_address;
}
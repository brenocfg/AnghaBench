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
struct pp_hwmgr {int dummy; } ;
struct TYPE_3__ {int numEntries; } ;
typedef  TYPE_1__ ATOM_PPLIB_VCE_State_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_POWERPLAYTABLE ;

/* Variables and functions */
 int /*<<< orphan*/ * get_powerplay_table (struct pp_hwmgr*) ; 
 TYPE_1__* get_vce_state_table (struct pp_hwmgr*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int get_number_of_vce_state_table_entries(
						  struct pp_hwmgr *hwmgr)
{
	const ATOM_PPLIB_POWERPLAYTABLE *table =
					     get_powerplay_table(hwmgr);
	const ATOM_PPLIB_VCE_State_Table *vce_table =
				    get_vce_state_table(hwmgr, table);

	if (vce_table)
		return vce_table->numEntries;

	return 0;
}
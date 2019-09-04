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
struct pp_hwmgr {scalar_t__ pp_table_version; } ;

/* Variables and functions */
 scalar_t__ PP_TABLE_V0 ; 
 scalar_t__ PP_TABLE_V1 ; 
 int get_number_of_powerplay_table_entries_v1_0 (struct pp_hwmgr*) ; 
 int pp_tables_get_num_of_entries (struct pp_hwmgr*,unsigned long*) ; 

__attribute__((used)) static int smu7_get_number_of_powerplay_table_entries(struct pp_hwmgr *hwmgr)
{
	int result;
	unsigned long ret = 0;

	if (hwmgr->pp_table_version == PP_TABLE_V0) {
		result = pp_tables_get_num_of_entries(hwmgr, &ret);
		return result ? 0 : ret;
	} else if (hwmgr->pp_table_version == PP_TABLE_V1) {
		result = get_number_of_powerplay_table_entries_v1_0(hwmgr);
		return result;
	}
	return 0;
}
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
struct pp_hwmgr {scalar_t__ pp_table_version; int /*<<< orphan*/ * pptable_func; int /*<<< orphan*/ * hwmgr_func; } ;

/* Variables and functions */
 scalar_t__ PP_TABLE_V0 ; 
 scalar_t__ PP_TABLE_V1 ; 
 int /*<<< orphan*/  pptable_funcs ; 
 int /*<<< orphan*/  pptable_v1_0_funcs ; 
 int /*<<< orphan*/  smu7_hwmgr_funcs ; 

int smu7_init_function_pointers(struct pp_hwmgr *hwmgr)
{
	int ret = 0;

	hwmgr->hwmgr_func = &smu7_hwmgr_funcs;
	if (hwmgr->pp_table_version == PP_TABLE_V0)
		hwmgr->pptable_func = &pptable_funcs;
	else if (hwmgr->pp_table_version == PP_TABLE_V1)
		hwmgr->pptable_func = &pptable_v1_0_funcs;

	return ret;
}
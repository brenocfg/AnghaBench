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
struct pp_hwmgr {TYPE_1__* smumgr_funcs; } ;
struct TYPE_2__ {int (* populate_all_memory_levels ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int stub1 (struct pp_hwmgr*) ; 

int smum_populate_all_memory_levels(struct pp_hwmgr *hwmgr)
{
	if (NULL != hwmgr->smumgr_funcs->populate_all_memory_levels)
		return hwmgr->smumgr_funcs->populate_all_memory_levels(hwmgr);

	return 0;
}
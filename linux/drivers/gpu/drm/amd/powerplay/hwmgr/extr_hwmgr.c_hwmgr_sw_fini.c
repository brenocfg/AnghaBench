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
struct TYPE_2__ {int /*<<< orphan*/  (* smu_fini ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct pp_hwmgr*) ; 

int hwmgr_sw_fini(struct pp_hwmgr *hwmgr)
{
	if (hwmgr && hwmgr->smumgr_funcs && hwmgr->smumgr_funcs->smu_fini)
		hwmgr->smumgr_funcs->smu_fini(hwmgr);

	return 0;
}
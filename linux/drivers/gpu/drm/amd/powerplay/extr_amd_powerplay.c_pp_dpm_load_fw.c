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
struct TYPE_2__ {scalar_t__ (* start_smu ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ stub1 (struct pp_hwmgr*) ; 

__attribute__((used)) static int pp_dpm_load_fw(void *handle)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->smumgr_funcs || !hwmgr->smumgr_funcs->start_smu)
		return -EINVAL;

	if (hwmgr->smumgr_funcs->start_smu(hwmgr)) {
		pr_err("fw load failed\n");
		return -EINVAL;
	}

	return 0;
}
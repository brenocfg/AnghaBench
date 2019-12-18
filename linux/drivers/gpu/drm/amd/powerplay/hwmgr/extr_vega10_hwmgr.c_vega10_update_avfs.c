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
struct vega10_hwmgr {int need_update_dpm_table; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;

/* Variables and functions */
 int DPMTABLE_OD_UPDATE_VDDC ; 
 int /*<<< orphan*/  vega10_avfs_enable (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int vega10_update_avfs(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	if (data->need_update_dpm_table & DPMTABLE_OD_UPDATE_VDDC) {
		vega10_avfs_enable(hwmgr, false);
	} else if (data->need_update_dpm_table) {
		vega10_avfs_enable(hwmgr, false);
		vega10_avfs_enable(hwmgr, true);
	} else {
		vega10_avfs_enable(hwmgr, true);
	}

	return 0;
}
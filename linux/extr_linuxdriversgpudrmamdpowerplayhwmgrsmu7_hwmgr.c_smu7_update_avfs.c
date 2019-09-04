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
struct smu7_hwmgr {int need_update_smu7_dpm_table; } ;
struct pp_hwmgr {int /*<<< orphan*/  avfs_supported; scalar_t__ backend; } ;

/* Variables and functions */
 int DPMTABLE_OD_UPDATE_SCLK ; 
 int DPMTABLE_OD_UPDATE_VDDC ; 
 int /*<<< orphan*/  smu7_avfs_control (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int smu7_update_avfs(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (!hwmgr->avfs_supported)
		return 0;

	if (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_VDDC) {
		smu7_avfs_control(hwmgr, false);
	} else if (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_SCLK) {
		smu7_avfs_control(hwmgr, false);
		smu7_avfs_control(hwmgr, true);
	} else {
		smu7_avfs_control(hwmgr, true);
	}

	return 0;
}
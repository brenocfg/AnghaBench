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
struct TYPE_2__ {int (* update_dpm_settings ) (struct pp_hwmgr*,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct pp_hwmgr*,void*) ; 

int smum_update_dpm_settings(struct pp_hwmgr *hwmgr, void *profile_setting)
{
	if (hwmgr->smumgr_funcs->update_dpm_settings)
		return hwmgr->smumgr_funcs->update_dpm_settings(hwmgr, profile_setting);

	return -EINVAL;
}
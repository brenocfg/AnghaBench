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
struct pp_hwmgr {TYPE_1__* hwmgr_func; int /*<<< orphan*/  pm_en; } ;
typedef  enum pp_mp1_state { ____Placeholder_pp_mp1_state } pp_mp1_state ;
struct TYPE_2__ {int (* set_mp1_state ) (struct pp_hwmgr*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int pp_dpm_set_mp1_state(void *handle, enum pp_mp1_state mp1_state)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (hwmgr->hwmgr_func->set_mp1_state)
		return hwmgr->hwmgr_func->set_mp1_state(hwmgr, mp1_state);

	return 0;
}
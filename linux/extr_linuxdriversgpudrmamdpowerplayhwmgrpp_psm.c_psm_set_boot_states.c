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
struct pp_hwmgr {int /*<<< orphan*/  ps; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_Boot ; 
 int /*<<< orphan*/  psm_get_state_by_classification (struct pp_hwmgr*,int /*<<< orphan*/ ,unsigned long*) ; 
 int psm_set_states (struct pp_hwmgr*,unsigned long) ; 

int psm_set_boot_states(struct pp_hwmgr *hwmgr)
{
	unsigned long state_id;
	int ret = -EINVAL;

	if (!hwmgr->ps)
		return 0;

	if (!psm_get_state_by_classification(hwmgr, PP_StateClassificationFlag_Boot,
					&state_id))
		ret = psm_set_states(hwmgr, state_id);

	return ret;
}
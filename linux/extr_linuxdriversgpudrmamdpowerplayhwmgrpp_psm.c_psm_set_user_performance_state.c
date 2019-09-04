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
struct TYPE_2__ {int ui_label; } ;
struct pp_power_state {TYPE_1__ classification; } ;
struct pp_hwmgr {int num_ps; scalar_t__ ps_size; struct pp_power_state* ps; } ;
typedef  enum PP_StateUILabel { ____Placeholder_PP_StateUILabel } PP_StateUILabel ;

/* Variables and functions */
 int EINVAL ; 
#define  PP_StateUILabel_Balanced 129 
#define  PP_StateUILabel_Battery 128 
 int PP_StateUILabel_Performance ; 

int psm_set_user_performance_state(struct pp_hwmgr *hwmgr,
					enum PP_StateUILabel label_id,
					struct pp_power_state **state)
{
	int table_entries;
	int i;

	if (!hwmgr->ps)
		return 0;

	table_entries = hwmgr->num_ps;
	*state = hwmgr->ps;

restart_search:
	for (i = 0; i < table_entries; i++) {
		if ((*state)->classification.ui_label & label_id)
			return 0;
		*state = (struct pp_power_state *)((uintptr_t)*state + hwmgr->ps_size);
	}

	switch (label_id) {
	case PP_StateUILabel_Battery:
	case PP_StateUILabel_Balanced:
		label_id = PP_StateUILabel_Performance;
		goto restart_search;
	default:
		break;
	}
	return -EINVAL;
}
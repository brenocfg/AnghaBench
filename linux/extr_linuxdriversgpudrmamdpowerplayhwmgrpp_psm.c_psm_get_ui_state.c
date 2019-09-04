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
struct pp_power_state {unsigned long id; TYPE_1__ classification; } ;
struct pp_hwmgr {int num_ps; scalar_t__ ps_size; struct pp_power_state* ps; } ;
typedef  enum PP_StateUILabel { ____Placeholder_PP_StateUILabel } PP_StateUILabel ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int psm_get_ui_state(struct pp_hwmgr *hwmgr,
				enum PP_StateUILabel ui_label,
				unsigned long *state_id)
{
	struct pp_power_state *state;
	int table_entries;
	int i;

	table_entries = hwmgr->num_ps;
	state = hwmgr->ps;

	for (i = 0; i < table_entries; i++) {
		if (state->classification.ui_label & ui_label) {
			*state_id = state->id;
			return 0;
		}
		state = (struct pp_power_state *)((unsigned long)state + hwmgr->ps_size);
	}
	return -EINVAL;
}
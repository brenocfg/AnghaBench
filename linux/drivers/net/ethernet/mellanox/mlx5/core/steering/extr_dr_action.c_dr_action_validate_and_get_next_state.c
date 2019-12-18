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
typedef  size_t u32 ;
typedef  enum dr_action_domain { ____Placeholder_dr_action_domain } dr_action_domain ;

/* Variables and functions */
 size_t DR_ACTION_STATE_ERR ; 
 int EOPNOTSUPP ; 
 size_t*** next_action_state ; 

__attribute__((used)) static
int dr_action_validate_and_get_next_state(enum dr_action_domain action_domain,
					  u32 action_type,
					  u32 *state)
{
	u32 cur_state = *state;

	/* Check action state machine is valid */
	*state = next_action_state[action_domain][cur_state][action_type];

	if (*state == DR_ACTION_STATE_ERR)
		return -EOPNOTSUPP;

	return 0;
}
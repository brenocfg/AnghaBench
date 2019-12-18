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
struct smu_context {int dummy; } ;
struct pp_states_info {int nums; int /*<<< orphan*/ * states; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_DEFAULT ; 
 int /*<<< orphan*/  memset (struct pp_states_info*,int /*<<< orphan*/ ,int) ; 

int smu_get_power_num_states(struct smu_context *smu,
			     struct pp_states_info *state_info)
{
	if (!state_info)
		return -EINVAL;

	/* not support power state */
	memset(state_info, 0, sizeof(struct pp_states_info));
	state_info->nums = 1;
	state_info->states[0] = POWER_STATE_TYPE_DEFAULT;

	return 0;
}
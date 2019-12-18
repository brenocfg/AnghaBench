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
struct cpuidle_state {int exit_latency; int /*<<< orphan*/  name; } ;
struct cpuidle_driver {int state_count; struct cpuidle_state* states; } ;

/* Variables and functions */
 struct cpuidle_driver* cpuidle_get_driver () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int cstate_disable_latency(const char *name)
{
	const struct cpuidle_driver *drv;
	int i;

	drv = cpuidle_get_driver();
	if (!drv)
		return 0;

	for (i = 0; i < drv->state_count; i++) {
		const struct cpuidle_state *state = &drv->states[i];

		if (!strcmp(state->name, name))
			return state->exit_latency ?
				state->exit_latency - 1 : 0;
	}

	return 0;
}
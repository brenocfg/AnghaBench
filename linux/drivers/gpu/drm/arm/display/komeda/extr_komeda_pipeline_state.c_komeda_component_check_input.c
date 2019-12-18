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
struct komeda_component_state {int /*<<< orphan*/  active_inputs; struct komeda_component* component; } ;
struct komeda_component_output {TYPE_1__* component; } ;
struct komeda_component {int max_active_inputs; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 scalar_t__ has_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
komeda_component_check_input(struct komeda_component_state *state,
			     struct komeda_component_output *input,
			     int idx)
{
	struct komeda_component *c = state->component;

	if ((idx < 0) || (idx >= c->max_active_inputs)) {
		DRM_DEBUG_ATOMIC("%s required an invalid %s-input[%d].\n",
				 input->component->name, c->name, idx);
		return -EINVAL;
	}

	if (has_bit(idx, state->active_inputs)) {
		DRM_DEBUG_ATOMIC("%s required %s-input[%d] has been occupied already.\n",
				 input->component->name, c->name, idx);
		return -EINVAL;
	}

	return 0;
}
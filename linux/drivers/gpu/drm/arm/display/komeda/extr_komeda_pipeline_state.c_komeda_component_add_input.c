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
struct komeda_component_state {int /*<<< orphan*/  affected_inputs; int /*<<< orphan*/  active_inputs; int /*<<< orphan*/  changed_active_inputs; int /*<<< orphan*/ * inputs; struct komeda_component* component; } ;
struct komeda_component_output {int dummy; } ;
struct komeda_component {int max_active_inputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  has_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct komeda_component_output*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct komeda_component_output*,int) ; 

__attribute__((used)) static void
komeda_component_add_input(struct komeda_component_state *state,
			   struct komeda_component_output *input,
			   int idx)
{
	struct komeda_component *c = state->component;

	WARN_ON((idx < 0 || idx >= c->max_active_inputs));

	/* since the inputs[i] is only valid when it is active. So if a input[i]
	 * is a newly enabled input which switches from disable to enable, then
	 * the old inputs[i] is undefined (NOT zeroed), we can not rely on
	 * memcmp, but directly mark it changed
	 */
	if (!has_bit(idx, state->affected_inputs) ||
	    memcmp(&state->inputs[idx], input, sizeof(*input))) {
		memcpy(&state->inputs[idx], input, sizeof(*input));
		state->changed_active_inputs |= BIT(idx);
	}
	state->active_inputs |= BIT(idx);
	state->affected_inputs |= BIT(idx);
}
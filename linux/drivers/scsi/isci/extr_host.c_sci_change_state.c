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
typedef  size_t u32 ;
struct sci_base_state_machine {size_t current_state_id; size_t previous_state_id; TYPE_1__* state_table; } ;
typedef  int /*<<< orphan*/  (* sci_state_transition_t ) (struct sci_base_state_machine*) ;
struct TYPE_2__ {int /*<<< orphan*/  (* enter_state ) (struct sci_base_state_machine*) ;int /*<<< orphan*/  (* exit_state ) (struct sci_base_state_machine*) ;} ;

/* Variables and functions */

void sci_change_state(struct sci_base_state_machine *sm, u32 next_state)
{
	sci_state_transition_t handler;

	handler = sm->state_table[sm->current_state_id].exit_state;
	if (handler)
		handler(sm);

	sm->previous_state_id = sm->current_state_id;
	sm->current_state_id = next_state;

	handler = sm->state_table[sm->current_state_id].enter_state;
	if (handler)
		handler(sm);
}
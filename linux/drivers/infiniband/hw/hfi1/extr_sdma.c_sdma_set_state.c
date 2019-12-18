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
struct sdma_state {size_t current_state; size_t previous_state; unsigned int previous_op; unsigned int current_op; int go_s99_running; } ;
struct sdma_set_state_action {scalar_t__ go_s99_running_totrue; scalar_t__ go_s99_running_tofalse; scalar_t__ op_cleanup; scalar_t__ op_halt; scalar_t__ op_intenable; scalar_t__ op_enable; } ;
struct sdma_engine {struct sdma_state state; } ;
typedef  enum sdma_states { ____Placeholder_sdma_states } sdma_states ;

/* Variables and functions */
 unsigned int SDMA_SENDCTRL_OP_CLEANUP ; 
 unsigned int SDMA_SENDCTRL_OP_ENABLE ; 
 unsigned int SDMA_SENDCTRL_OP_HALT ; 
 unsigned int SDMA_SENDCTRL_OP_INTENABLE ; 
 struct sdma_set_state_action* sdma_action_table ; 
 int /*<<< orphan*/  sdma_flush (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_sendctrl (struct sdma_engine*,unsigned int) ; 
 int /*<<< orphan*/ * sdma_state_names ; 
 int sdma_state_s99_running ; 
 int /*<<< orphan*/  trace_hfi1_sdma_state (struct sdma_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_set_state(struct sdma_engine *sde,
			   enum sdma_states next_state)
{
	struct sdma_state *ss = &sde->state;
	const struct sdma_set_state_action *action = sdma_action_table;
	unsigned op = 0;

	trace_hfi1_sdma_state(
		sde,
		sdma_state_names[ss->current_state],
		sdma_state_names[next_state]);

	/* debugging bookkeeping */
	ss->previous_state = ss->current_state;
	ss->previous_op = ss->current_op;
	ss->current_state = next_state;

	if (ss->previous_state != sdma_state_s99_running &&
	    next_state == sdma_state_s99_running)
		sdma_flush(sde);

	if (action[next_state].op_enable)
		op |= SDMA_SENDCTRL_OP_ENABLE;

	if (action[next_state].op_intenable)
		op |= SDMA_SENDCTRL_OP_INTENABLE;

	if (action[next_state].op_halt)
		op |= SDMA_SENDCTRL_OP_HALT;

	if (action[next_state].op_cleanup)
		op |= SDMA_SENDCTRL_OP_CLEANUP;

	if (action[next_state].go_s99_running_tofalse)
		ss->go_s99_running = 0;

	if (action[next_state].go_s99_running_totrue)
		ss->go_s99_running = 1;

	ss->current_op = op;
	sdma_sendctrl(sde, ss->current_op);
}
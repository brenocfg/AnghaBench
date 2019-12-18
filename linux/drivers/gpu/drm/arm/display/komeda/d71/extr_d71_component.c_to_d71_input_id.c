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
typedef  scalar_t__ u32 ;
struct komeda_component_state {int /*<<< orphan*/  active_inputs; struct komeda_component_output* inputs; } ;
struct komeda_component_output {scalar_t__ output_port; TYPE_1__* component; } ;
struct TYPE_2__ {scalar_t__ hw_id; } ;

/* Variables and functions */
 scalar_t__ has_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 to_d71_input_id(struct komeda_component_state *st, int idx)
{
	struct komeda_component_output *input = &st->inputs[idx];

	/* if input is not active, set hw input_id(0) to disable it */
	if (has_bit(idx, st->active_inputs))
		return input->component->hw_id + input->output_port;
	else
		return 0;
}
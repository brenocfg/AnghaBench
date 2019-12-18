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
struct komeda_component_state {scalar_t__ changed_active_inputs; scalar_t__ active_inputs; scalar_t__ affected_inputs; int /*<<< orphan*/ * binding_user; } ;

/* Variables and functions */

__attribute__((used)) static void
komeda_component_state_reset(struct komeda_component_state *st)
{
	st->binding_user = NULL;
	st->affected_inputs = st->active_inputs;
	st->active_inputs = 0;
	st->changed_active_inputs = 0;
}
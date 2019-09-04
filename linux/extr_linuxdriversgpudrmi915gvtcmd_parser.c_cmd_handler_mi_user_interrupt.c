#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct parser_exec_state {size_t ring_id; TYPE_1__* workload; } ;
struct TYPE_4__ {int /*<<< orphan*/  mi_user_interrupt; } ;
struct TYPE_3__ {int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_NOOP ; 
 TYPE_2__* cmd_interrupt_events ; 
 int /*<<< orphan*/  cmd_ptr (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  patch_value (struct parser_exec_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_handler_mi_user_interrupt(struct parser_exec_state *s)
{
	set_bit(cmd_interrupt_events[s->ring_id].mi_user_interrupt,
			s->workload->pending_events);
	patch_value(s, cmd_ptr(s, 0), MI_NOOP);
	return 0;
}
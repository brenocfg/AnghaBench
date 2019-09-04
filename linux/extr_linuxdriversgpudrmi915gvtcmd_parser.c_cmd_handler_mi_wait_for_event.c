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
typedef  int /*<<< orphan*/  u32 ;
struct parser_exec_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_NOOP ; 
 int /*<<< orphan*/  cmd_ptr (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_val (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_wait_for_flip_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  patch_value (struct parser_exec_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_handler_mi_wait_for_event(struct parser_exec_state *s)
{
	u32 cmd = cmd_val(s, 0);

	if (!is_wait_for_flip_pending(cmd))
		return 0;

	patch_value(s, cmd_ptr(s, 0), MI_NOOP);
	return 0;
}
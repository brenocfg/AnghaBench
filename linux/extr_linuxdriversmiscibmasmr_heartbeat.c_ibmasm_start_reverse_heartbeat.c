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
struct service_processor {int dummy; } ;
struct reverse_heartbeat {scalar_t__ stopped; int /*<<< orphan*/  wait; } ;
struct command {scalar_t__ status; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 int HZ ; 
 scalar_t__ IBMASM_CMD_COMPLETE ; 
 scalar_t__ IBMASM_CMD_PENDING ; 
 int /*<<< orphan*/  IBMASM_CMD_TIMEOUT_NORMAL ; 
 int REVERSE_HEARTBEAT_TIMEOUT ; 
 int /*<<< orphan*/  command_put (struct command*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ibmasm_exec_command (struct service_processor*,struct command*) ; 
 struct command* ibmasm_new_command (struct service_processor*,int) ; 
 int /*<<< orphan*/  ibmasm_wait_for_response (struct command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  rhb_dot_cmd ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

int ibmasm_start_reverse_heartbeat(struct service_processor *sp, struct reverse_heartbeat *rhb)
{
	struct command *cmd;
	int times_failed = 0;
	int result = 1;

	cmd = ibmasm_new_command(sp, sizeof rhb_dot_cmd);
	if (!cmd)
		return -ENOMEM;

	while (times_failed < 3) {
		memcpy(cmd->buffer, (void *)&rhb_dot_cmd, sizeof rhb_dot_cmd);
		cmd->status = IBMASM_CMD_PENDING;
		ibmasm_exec_command(sp, cmd);
		ibmasm_wait_for_response(cmd, IBMASM_CMD_TIMEOUT_NORMAL);

		if (cmd->status != IBMASM_CMD_COMPLETE)
			times_failed++;

		wait_event_interruptible_timeout(rhb->wait,
			rhb->stopped,
			REVERSE_HEARTBEAT_TIMEOUT * HZ);

		if (signal_pending(current) || rhb->stopped) {
			result = -EINTR;
			break;
		}
	}
	command_put(cmd);
	rhb->stopped = 0;

	return result;
}
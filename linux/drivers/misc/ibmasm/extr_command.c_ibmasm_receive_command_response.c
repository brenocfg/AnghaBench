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
struct service_processor {struct command* current_command; } ;
struct command {int /*<<< orphan*/  wait; int /*<<< orphan*/  status; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMASM_CMD_COMPLETE ; 
 int /*<<< orphan*/  command_put (struct command*) ; 
 int /*<<< orphan*/  exec_next_command (struct service_processor*) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ibmasm_receive_command_response(struct service_processor *sp, void *response, size_t size)
{
	struct command *cmd = sp->current_command;

	if (!sp->current_command)
		return;

	memcpy_fromio(cmd->buffer, response, min(size, cmd->buffer_size));
	cmd->status = IBMASM_CMD_COMPLETE;
	wake_up(&sp->current_command->wait);
	command_put(sp->current_command);
	exec_next_command(sp);
}
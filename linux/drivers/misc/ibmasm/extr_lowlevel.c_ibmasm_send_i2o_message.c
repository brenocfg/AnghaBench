#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct service_processor {int /*<<< orphan*/  base_address; struct command* current_command; } ;
struct i2o_message {int /*<<< orphan*/  data; int /*<<< orphan*/  header; } ;
struct i2o_header {int dummy; } ;
struct command {TYPE_1__* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  message_size; } ;

/* Variables and functions */
 unsigned int get_dot_command_size (TYPE_1__*) ; 
 struct i2o_message* get_i2o_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mfa_inbound (int /*<<< orphan*/ ) ; 
 TYPE_1__ header ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  outgoing_message_size (unsigned int) ; 
 int /*<<< orphan*/  set_mfa_inbound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ibmasm_send_i2o_message(struct service_processor *sp)
{
	u32 mfa;
	unsigned int command_size;
	struct i2o_message *message;
	struct command *command = sp->current_command;

	mfa = get_mfa_inbound(sp->base_address);
	if (!mfa)
		return 1;

	command_size = get_dot_command_size(command->buffer);
	header.message_size = outgoing_message_size(command_size);

	message = get_i2o_message(sp->base_address, mfa);

	memcpy_toio(&message->header, &header, sizeof(struct i2o_header));
	memcpy_toio(&message->data, command->buffer, command_size);

	set_mfa_inbound(sp->base_address, mfa);

	return 0;
}
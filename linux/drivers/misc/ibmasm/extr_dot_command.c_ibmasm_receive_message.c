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
typedef  int u32 ;
struct service_processor {int /*<<< orphan*/  dev; } ;
struct dot_command_header {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_dot_command_size (void*) ; 
 int /*<<< orphan*/  ibmasm_receive_command_response (struct service_processor*,void*,int) ; 
 int /*<<< orphan*/  ibmasm_receive_event (struct service_processor*,void*,int) ; 
 int /*<<< orphan*/  ibmasm_receive_heartbeat (struct service_processor*,void*,int) ; 
#define  sp_command_response 130 
#define  sp_event 129 
#define  sp_heartbeat 128 

void ibmasm_receive_message(struct service_processor *sp, void *message, int message_size)
{
	u32 size;
	struct dot_command_header *header = (struct dot_command_header *)message;

	if (message_size == 0)
		return;

	size = get_dot_command_size(message);
	if (size == 0)
		return;

	if (size > message_size)
		size = message_size;

	switch (header->type) {
	case sp_event:
		ibmasm_receive_event(sp, message, size);
		break;
	case sp_command_response:
		ibmasm_receive_command_response(sp, message, size);
		break;
	case sp_heartbeat:
		ibmasm_receive_heartbeat(sp, message, size);
		break;
	default:
		dev_err(sp->dev, "Received unknown message from service processor\n");
	}
}
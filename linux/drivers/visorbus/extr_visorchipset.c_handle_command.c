#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct parser_context {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  phys_device; } ;
struct TYPE_11__ {TYPE_1__ flags; } ;
struct controlvm_message_packet {TYPE_2__ device_change_state; } ;
struct TYPE_12__ {int /*<<< orphan*/  response_expected; } ;
struct TYPE_13__ {int id; TYPE_3__ flags; scalar_t__ payload_bytes; scalar_t__ payload_vm_offset; } ;
struct controlvm_message {TYPE_4__ hdr; struct controlvm_message_packet cmd; } ;
struct TYPE_14__ {int /*<<< orphan*/  controlvm_channel; } ;

/* Variables and functions */
#define  CONTROLVM_BUS_CONFIGURE 138 
#define  CONTROLVM_BUS_CREATE 137 
#define  CONTROLVM_BUS_DESTROY 136 
#define  CONTROLVM_CHIPSET_INIT 135 
#define  CONTROLVM_CHIPSET_READY 134 
#define  CONTROLVM_CHIPSET_SELFTEST 133 
#define  CONTROLVM_CHIPSET_STOP 132 
#define  CONTROLVM_DEVICE_CHANGESTATE 131 
#define  CONTROLVM_DEVICE_CONFIGURE 130 
#define  CONTROLVM_DEVICE_CREATE 129 
#define  CONTROLVM_DEVICE_DESTROY 128 
 int /*<<< orphan*/  CONTROLVM_QUEUE_ACK ; 
 int /*<<< orphan*/  CONTROLVM_RESP_ID_UNKNOWN ; 
 int /*<<< orphan*/  CONTROLVM_RESP_SUCCESS ; 
 int EAGAIN ; 
 int ENOMSG ; 
 TYPE_9__* chipset_dev ; 
 int chipset_init (struct controlvm_message*) ; 
 int chipset_notready_uevent (TYPE_4__*) ; 
 int chipset_ready_uevent (TYPE_4__*) ; 
 int chipset_selftest_uevent (TYPE_4__*) ; 
 int /*<<< orphan*/  controlvm_init_response (struct controlvm_message*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  controlvm_respond (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parahotplug_process_message (struct controlvm_message*) ; 
 int /*<<< orphan*/  parser_done (struct parser_context*) ; 
 struct parser_context* parser_init_stream (scalar_t__,scalar_t__,int*) ; 
 int visorbus_configure (struct controlvm_message*,struct parser_context*) ; 
 int visorbus_create (struct controlvm_message*) ; 
 int visorbus_destroy (struct controlvm_message*) ; 
 int visorbus_device_changestate (struct controlvm_message*) ; 
 int visorbus_device_create (struct controlvm_message*) ; 
 int visorbus_device_destroy (struct controlvm_message*) ; 
 int visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct controlvm_message*) ; 

__attribute__((used)) static int handle_command(struct controlvm_message inmsg, u64 channel_addr)
{
	struct controlvm_message_packet *cmd = &inmsg.cmd;
	u64 parm_addr;
	u32 parm_bytes;
	struct parser_context *parser_ctx = NULL;
	struct controlvm_message ackmsg;
	int err = 0;

	/* create parsing context if necessary */
	parm_addr = channel_addr + inmsg.hdr.payload_vm_offset;
	parm_bytes = inmsg.hdr.payload_bytes;
	/*
	 * Parameter and channel addresses within test messages actually lie
	 * within our OS-controlled memory. We need to know that, because it
	 * makes a difference in how we compute the virtual address.
	 */
	if (parm_bytes) {
		bool retry;

		parser_ctx = parser_init_stream(parm_addr, parm_bytes, &retry);
		if (!parser_ctx && retry)
			return -EAGAIN;
	}
	controlvm_init_response(&ackmsg, &inmsg.hdr, CONTROLVM_RESP_SUCCESS);
	err = visorchannel_signalinsert(chipset_dev->controlvm_channel,
					CONTROLVM_QUEUE_ACK, &ackmsg);
	if (err)
		return err;
	switch (inmsg.hdr.id) {
	case CONTROLVM_CHIPSET_INIT:
		err = chipset_init(&inmsg);
		break;
	case CONTROLVM_BUS_CREATE:
		err = visorbus_create(&inmsg);
		break;
	case CONTROLVM_BUS_DESTROY:
		err = visorbus_destroy(&inmsg);
		break;
	case CONTROLVM_BUS_CONFIGURE:
		err = visorbus_configure(&inmsg, parser_ctx);
		break;
	case CONTROLVM_DEVICE_CREATE:
		err = visorbus_device_create(&inmsg);
		break;
	case CONTROLVM_DEVICE_CHANGESTATE:
		if (cmd->device_change_state.flags.phys_device) {
			err = parahotplug_process_message(&inmsg);
		} else {
			/*
			 * save the hdr and cmd structures for later use when
			 * sending back the response to Command
			 */
			err = visorbus_device_changestate(&inmsg);
			break;
		}
		break;
	case CONTROLVM_DEVICE_DESTROY:
		err = visorbus_device_destroy(&inmsg);
		break;
	case CONTROLVM_DEVICE_CONFIGURE:
		/* no op just send a respond that we passed */
		if (inmsg.hdr.flags.response_expected)
			controlvm_respond(&inmsg.hdr, CONTROLVM_RESP_SUCCESS,
					  NULL);
		break;
	case CONTROLVM_CHIPSET_READY:
		err = chipset_ready_uevent(&inmsg.hdr);
		break;
	case CONTROLVM_CHIPSET_SELFTEST:
		err = chipset_selftest_uevent(&inmsg.hdr);
		break;
	case CONTROLVM_CHIPSET_STOP:
		err = chipset_notready_uevent(&inmsg.hdr);
		break;
	default:
		err = -ENOMSG;
		if (inmsg.hdr.flags.response_expected)
			controlvm_respond(&inmsg.hdr,
					  -CONTROLVM_RESP_ID_UNKNOWN, NULL);
		break;
	}
	if (parser_ctx) {
		parser_done(parser_ctx);
		parser_ctx = NULL;
	}
	return err;
}
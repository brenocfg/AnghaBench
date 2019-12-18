#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * key; } ;
struct hv_kvp_msg_enumerate {TYPE_2__ data; } ;
struct TYPE_4__ {struct hv_kvp_msg_enumerate kvp_enum_data; } ;
struct hv_kvp_msg {int error; TYPE_1__ body; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  recv_channel; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HVUTIL_READY ; 
 scalar_t__ HVUTIL_USERSPACE_RECV ; 
 scalar_t__ HVUTIL_USERSPACE_REQ ; 
 int HV_S_CONT ; 
#define  KVP_OP_REGISTER 129 
#define  KVP_OP_REGISTER1 128 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int dm_reg_value ; 
 int /*<<< orphan*/  hv_poll_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvp_handle_handshake (struct hv_kvp_msg*) ; 
 int /*<<< orphan*/  kvp_poll_wrapper ; 
 int /*<<< orphan*/  kvp_respond_to_host (struct hv_kvp_msg*,int) ; 
 int /*<<< orphan*/  kvp_timeout_work ; 
 TYPE_3__ kvp_transaction ; 

__attribute__((used)) static int kvp_on_msg(void *msg, int len)
{
	struct hv_kvp_msg *message = (struct hv_kvp_msg *)msg;
	struct hv_kvp_msg_enumerate *data;
	int	error = 0;

	if (len < sizeof(*message))
		return -EINVAL;

	/*
	 * If we are negotiating the version information
	 * with the daemon; handle that first.
	 */

	if (kvp_transaction.state < HVUTIL_READY) {
		return kvp_handle_handshake(message);
	}

	/* We didn't send anything to userspace so the reply is spurious */
	if (kvp_transaction.state < HVUTIL_USERSPACE_REQ)
		return -EINVAL;

	kvp_transaction.state = HVUTIL_USERSPACE_RECV;

	/*
	 * Based on the version of the daemon, we propagate errors from the
	 * daemon differently.
	 */

	data = &message->body.kvp_enum_data;

	switch (dm_reg_value) {
	case KVP_OP_REGISTER:
		/*
		 * Null string is used to pass back error condition.
		 */
		if (data->data.key[0] == 0)
			error = HV_S_CONT;
		break;

	case KVP_OP_REGISTER1:
		/*
		 * We use the message header information from
		 * the user level daemon to transmit errors.
		 */
		error = message->error;
		break;
	}

	/*
	 * Complete the transaction by forwarding the key value
	 * to the host. But first, cancel the timeout.
	 */
	if (cancel_delayed_work_sync(&kvp_timeout_work)) {
		kvp_respond_to_host(message, error);
		hv_poll_channel(kvp_transaction.recv_channel, kvp_poll_wrapper);
	}

	return 0;
}
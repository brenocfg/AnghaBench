#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ operation; } ;
struct hv_vss_msg {int /*<<< orphan*/  error; TYPE_3__ vss_hdr; } ;
struct TYPE_8__ {scalar_t__ state; int /*<<< orphan*/  recv_channel; TYPE_2__* msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ vss_cf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HVUTIL_READY ; 
 scalar_t__ HVUTIL_USERSPACE_RECV ; 
 scalar_t__ HVUTIL_USERSPACE_REQ ; 
 int /*<<< orphan*/  VSS_HBU_NO_AUTO_RECOVERY ; 
 scalar_t__ VSS_OP_HOT_BACKUP ; 
 scalar_t__ VSS_OP_REGISTER ; 
 scalar_t__ VSS_OP_REGISTER1 ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_poll_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int vss_handle_handshake (struct hv_vss_msg*) ; 
 int /*<<< orphan*/  vss_poll_wrapper ; 
 int /*<<< orphan*/  vss_respond_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_timeout_work ; 
 TYPE_4__ vss_transaction ; 

__attribute__((used)) static int vss_on_msg(void *msg, int len)
{
	struct hv_vss_msg *vss_msg = (struct hv_vss_msg *)msg;

	if (len != sizeof(*vss_msg)) {
		pr_debug("VSS: Message size does not match length\n");
		return -EINVAL;
	}

	if (vss_msg->vss_hdr.operation == VSS_OP_REGISTER ||
	    vss_msg->vss_hdr.operation == VSS_OP_REGISTER1) {
		/*
		 * Don't process registration messages if we're in the middle
		 * of a transaction processing.
		 */
		if (vss_transaction.state > HVUTIL_READY) {
			pr_debug("VSS: Got unexpected registration request\n");
			return -EINVAL;
		}

		return vss_handle_handshake(vss_msg);
	} else if (vss_transaction.state == HVUTIL_USERSPACE_REQ) {
		vss_transaction.state = HVUTIL_USERSPACE_RECV;

		if (vss_msg->vss_hdr.operation == VSS_OP_HOT_BACKUP)
			vss_transaction.msg->vss_cf.flags =
				VSS_HBU_NO_AUTO_RECOVERY;

		if (cancel_delayed_work_sync(&vss_timeout_work)) {
			vss_respond_to_host(vss_msg->error);
			/* Transaction is finished, reset the state. */
			hv_poll_channel(vss_transaction.recv_channel,
					vss_poll_wrapper);
		}
	} else {
		/* This is a spurious call! */
		pr_debug("VSS: Transaction not active\n");
		return -EINVAL;
	}
	return 0;
}
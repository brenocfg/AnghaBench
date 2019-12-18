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
struct work_struct {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  recv_channel; TYPE_3__* msg; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int operation; } ;
struct TYPE_7__ {TYPE_2__ dm_info; TYPE_1__ vss_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVUTIL_HOSTMSG_RECEIVED ; 
 int /*<<< orphan*/  HVUTIL_READY ; 
 int /*<<< orphan*/  HV_E_FAIL ; 
#define  VSS_OP_FREEZE 131 
#define  VSS_OP_GET_DM_INFO 130 
#define  VSS_OP_HOT_BACKUP 129 
#define  VSS_OP_THAW 128 
 int /*<<< orphan*/  hv_poll_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  vss_poll_wrapper ; 
 int /*<<< orphan*/  vss_respond_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_send_op () ; 
 TYPE_4__ vss_transaction ; 

__attribute__((used)) static void vss_handle_request(struct work_struct *dummy)
{
	switch (vss_transaction.msg->vss_hdr.operation) {
	/*
	 * Initiate a "freeze/thaw" operation in the guest.
	 * We respond to the host once the operation is complete.
	 *
	 * We send the message to the user space daemon and the operation is
	 * performed in the daemon.
	 */
	case VSS_OP_THAW:
	case VSS_OP_FREEZE:
	case VSS_OP_HOT_BACKUP:
		if (vss_transaction.state < HVUTIL_READY) {
			/* Userspace is not registered yet */
			pr_debug("VSS: Not ready for request.\n");
			vss_respond_to_host(HV_E_FAIL);
			return;
		}

		pr_debug("VSS: Received request for op code: %d\n",
			vss_transaction.msg->vss_hdr.operation);
		vss_transaction.state = HVUTIL_HOSTMSG_RECEIVED;
		vss_send_op();
		return;
	case VSS_OP_GET_DM_INFO:
		vss_transaction.msg->dm_info.flags = 0;
		break;
	default:
		break;
	}

	vss_respond_to_host(0);
	hv_poll_channel(vss_transaction.recv_channel, vss_poll_wrapper);
}
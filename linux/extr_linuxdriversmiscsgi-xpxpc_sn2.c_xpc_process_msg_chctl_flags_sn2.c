#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* remote_GPs; } ;
struct TYPE_8__ {TYPE_2__ sn2; } ;
struct xpc_partition {TYPE_3__ sn; struct xpc_channel* channels; } ;
struct TYPE_10__ {scalar_t__ get; scalar_t__ put; } ;
struct TYPE_9__ {scalar_t__ get; scalar_t__ put; } ;
struct xpc_channel_sn2 {TYPE_5__ w_remote_GP; TYPE_4__ remote_GP; } ;
struct TYPE_6__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  msg_allocate_wq; int /*<<< orphan*/  n_on_msg_allocate_wq; int /*<<< orphan*/  n_to_notify; TYPE_1__ sn; } ;

/* Variables and functions */
 int XPC_C_CONNECTED ; 
 int XPC_C_CONNECTEDCALLOUT_MADE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpMsgDelivered ; 
 int /*<<< orphan*/  xpc_activate_kthreads (struct xpc_channel*,int) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_clear_local_msgqueue_flags_sn2 (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_clear_remote_msgqueue_flags_sn2 (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_ref (struct xpc_channel*) ; 
 int xpc_n_of_deliverable_payloads_sn2 (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_notify_senders_sn2 (struct xpc_channel*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
xpc_process_msg_chctl_flags_sn2(struct xpc_partition *part, int ch_number)
{
	struct xpc_channel *ch = &part->channels[ch_number];
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	int npayloads_sent;

	ch_sn2->remote_GP = part->sn.sn2.remote_GPs[ch_number];

	/* See what, if anything, has changed for each connected channel */

	xpc_msgqueue_ref(ch);

	if (ch_sn2->w_remote_GP.get == ch_sn2->remote_GP.get &&
	    ch_sn2->w_remote_GP.put == ch_sn2->remote_GP.put) {
		/* nothing changed since GPs were last pulled */
		xpc_msgqueue_deref(ch);
		return;
	}

	if (!(ch->flags & XPC_C_CONNECTED)) {
		xpc_msgqueue_deref(ch);
		return;
	}

	/*
	 * First check to see if messages recently sent by us have been
	 * received by the other side. (The remote GET value will have
	 * changed since we last looked at it.)
	 */

	if (ch_sn2->w_remote_GP.get != ch_sn2->remote_GP.get) {

		/*
		 * We need to notify any senders that want to be notified
		 * that their sent messages have been received by their
		 * intended recipients. We need to do this before updating
		 * w_remote_GP.get so that we don't allocate the same message
		 * queue entries prematurely (see xpc_allocate_msg()).
		 */
		if (atomic_read(&ch->n_to_notify) > 0) {
			/*
			 * Notify senders that messages sent have been
			 * received and delivered by the other side.
			 */
			xpc_notify_senders_sn2(ch, xpMsgDelivered,
					       ch_sn2->remote_GP.get);
		}

		/*
		 * Clear msg->flags in previously sent messages, so that
		 * they're ready for xpc_allocate_msg().
		 */
		xpc_clear_local_msgqueue_flags_sn2(ch);

		ch_sn2->w_remote_GP.get = ch_sn2->remote_GP.get;

		dev_dbg(xpc_chan, "w_remote_GP.get changed to %lld, partid=%d, "
			"channel=%d\n", ch_sn2->w_remote_GP.get, ch->partid,
			ch->number);

		/*
		 * If anyone was waiting for message queue entries to become
		 * available, wake them up.
		 */
		if (atomic_read(&ch->n_on_msg_allocate_wq) > 0)
			wake_up(&ch->msg_allocate_wq);
	}

	/*
	 * Now check for newly sent messages by the other side. (The remote
	 * PUT value will have changed since we last looked at it.)
	 */

	if (ch_sn2->w_remote_GP.put != ch_sn2->remote_GP.put) {
		/*
		 * Clear msg->flags in previously received messages, so that
		 * they're ready for xpc_get_deliverable_payload_sn2().
		 */
		xpc_clear_remote_msgqueue_flags_sn2(ch);

		smp_wmb(); /* ensure flags have been cleared before bte_copy */
		ch_sn2->w_remote_GP.put = ch_sn2->remote_GP.put;

		dev_dbg(xpc_chan, "w_remote_GP.put changed to %lld, partid=%d, "
			"channel=%d\n", ch_sn2->w_remote_GP.put, ch->partid,
			ch->number);

		npayloads_sent = xpc_n_of_deliverable_payloads_sn2(ch);
		if (npayloads_sent > 0) {
			dev_dbg(xpc_chan, "msgs waiting to be copied and "
				"delivered=%d, partid=%d, channel=%d\n",
				npayloads_sent, ch->partid, ch->number);

			if (ch->flags & XPC_C_CONNECTEDCALLOUT_MADE)
				xpc_activate_kthreads(ch, npayloads_sent);
		}
	}

	xpc_msgqueue_deref(ch);
}
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
struct xpc_partition_uv {scalar_t__ act_state_req; int /*<<< orphan*/  reason; } ;
struct TYPE_5__ {struct xpc_partition_uv uv; } ;
struct xpc_partition {int nchannels; struct xpc_channel* channels; TYPE_1__ sn; } ;
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
struct TYPE_8__ {int ch_number; scalar_t__ size; int msg_slot_number; TYPE_3__ u; } ;
struct xpc_notify_mq_msg_uv {TYPE_4__ hdr; } ;
struct xpc_channel_uv {int /*<<< orphan*/  recv_msg_list; struct xpc_notify_mq_msg_uv* recv_msg_slots; } ;
struct TYPE_6__ {struct xpc_channel_uv uv; } ;
struct xpc_channel {int flags; int remote_nentries; int entry_size; int /*<<< orphan*/  number; int /*<<< orphan*/  idle_wq; int /*<<< orphan*/  kthreads_idle; TYPE_2__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int XPC_C_CONNECTED ; 
 int XPC_C_CONNECTEDCALLOUT_MADE ; 
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 scalar_t__ XPC_P_ASR_DEACTIVATE_UV ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xpc_notify_mq_msg_uv*,struct xpc_notify_mq_msg_uv*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_nr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xpBadChannelNumber ; 
 int /*<<< orphan*/  xpc_activate_IRQ_rcvd ; 
 int /*<<< orphan*/  xpc_activate_IRQ_rcvd_lock ; 
 int /*<<< orphan*/  xpc_activate_IRQ_wq ; 
 int /*<<< orphan*/  xpc_handle_notify_mq_ack_uv (struct xpc_channel*,struct xpc_notify_mq_msg_uv*) ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_ref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_put_fifo_entry_uv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpc_send_chctl_local_msgrequest_uv (struct xpc_partition*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_handle_notify_mq_msg_uv(struct xpc_partition *part,
			    struct xpc_notify_mq_msg_uv *msg)
{
	struct xpc_partition_uv *part_uv = &part->sn.uv;
	struct xpc_channel *ch;
	struct xpc_channel_uv *ch_uv;
	struct xpc_notify_mq_msg_uv *msg_slot;
	unsigned long irq_flags;
	int ch_number = msg->hdr.ch_number;

	if (unlikely(ch_number >= part->nchannels)) {
		dev_err(xpc_part, "xpc_handle_notify_IRQ_uv() received invalid "
			"channel number=0x%x in message from partid=%d\n",
			ch_number, XPC_PARTID(part));

		/* get hb checker to deactivate from the remote partition */
		spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
		if (part_uv->act_state_req == 0)
			xpc_activate_IRQ_rcvd++;
		part_uv->act_state_req = XPC_P_ASR_DEACTIVATE_UV;
		part_uv->reason = xpBadChannelNumber;
		spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

		wake_up_interruptible(&xpc_activate_IRQ_wq);
		return;
	}

	ch = &part->channels[ch_number];
	xpc_msgqueue_ref(ch);

	if (!(ch->flags & XPC_C_CONNECTED)) {
		xpc_msgqueue_deref(ch);
		return;
	}

	/* see if we're really dealing with an ACK for a previously sent msg */
	if (msg->hdr.size == 0) {
		xpc_handle_notify_mq_ack_uv(ch, msg);
		xpc_msgqueue_deref(ch);
		return;
	}

	/* we're dealing with a normal message sent via the notify_mq */
	ch_uv = &ch->sn.uv;

	msg_slot = ch_uv->recv_msg_slots +
	    (msg->hdr.msg_slot_number % ch->remote_nentries) * ch->entry_size;

	BUG_ON(msg_slot->hdr.size != 0);

	memcpy(msg_slot, msg, msg->hdr.size);

	xpc_put_fifo_entry_uv(&ch_uv->recv_msg_list, &msg_slot->hdr.u.next);

	if (ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) {
		/*
		 * If there is an existing idle kthread get it to deliver
		 * the payload, otherwise we'll have to get the channel mgr
		 * for this partition to create a kthread to do the delivery.
		 */
		if (atomic_read(&ch->kthreads_idle) > 0)
			wake_up_nr(&ch->idle_wq, 1);
		else
			xpc_send_chctl_local_msgrequest_uv(part, ch->number);
	}
	xpc_msgqueue_deref(ch);
}
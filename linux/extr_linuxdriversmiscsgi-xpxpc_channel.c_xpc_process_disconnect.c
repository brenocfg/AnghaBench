#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int* flags; } ;
struct xpc_partition {scalar_t__ act_state; int /*<<< orphan*/  chctl_lock; TYPE_1__ chctl; int /*<<< orphan*/  nchannels_active; } ;
struct xpc_channel {size_t partid; int flags; size_t number; int delayed_chctl_flags; int /*<<< orphan*/  wdisconnect_wait; int /*<<< orphan*/  reason; scalar_t__ kthreads_idle_limit; scalar_t__ kthreads_assigned_limit; scalar_t__ remote_nentries; scalar_t__ local_nentries; scalar_t__ entry_size; int /*<<< orphan*/ * key; int /*<<< orphan*/ * func; int /*<<< orphan*/  n_to_notify; int /*<<< orphan*/  lock; int /*<<< orphan*/  references; int /*<<< orphan*/  kthreads_assigned; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* teardown_msg_structures ) (struct xpc_channel*) ;int /*<<< orphan*/  (* notify_senders_of_disconnect ) (struct xpc_channel*) ;int /*<<< orphan*/  (* send_chctl_closereply ) (struct xpc_channel*,unsigned long*) ;scalar_t__ (* partition_engaged ) (size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_CLOSEREPLY ; 
 int XPC_C_CLOSEREQUEST ; 
 int XPC_C_CONNECTEDCALLOUT_MADE ; 
 int XPC_C_DISCONNECTED ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_DISCONNECTINGCALLOUT_MADE ; 
 int XPC_C_RCLOSEREPLY ; 
 int XPC_C_RCLOSEREQUEST ; 
 int XPC_C_WASCONNECTED ; 
 int XPC_C_WDISCONNECT ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (size_t) ; 
 int /*<<< orphan*/  stub2 (struct xpc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  stub3 (struct xpc_channel*) ; 
 int /*<<< orphan*/  stub4 (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpDisconnected ; 
 TYPE_2__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_disconnect_callout (struct xpc_channel*,int /*<<< orphan*/ ) ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static void
xpc_process_disconnect(struct xpc_channel *ch, unsigned long *irq_flags)
{
	struct xpc_partition *part = &xpc_partitions[ch->partid];
	u32 channel_was_connected = (ch->flags & XPC_C_WASCONNECTED);

	DBUG_ON(!spin_is_locked(&ch->lock));

	if (!(ch->flags & XPC_C_DISCONNECTING))
		return;

	DBUG_ON(!(ch->flags & XPC_C_CLOSEREQUEST));

	/* make sure all activity has settled down first */

	if (atomic_read(&ch->kthreads_assigned) > 0 ||
	    atomic_read(&ch->references) > 0) {
		return;
	}
	DBUG_ON((ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) &&
		!(ch->flags & XPC_C_DISCONNECTINGCALLOUT_MADE));

	if (part->act_state == XPC_P_AS_DEACTIVATING) {
		/* can't proceed until the other side disengages from us */
		if (xpc_arch_ops.partition_engaged(ch->partid))
			return;

	} else {

		/* as long as the other side is up do the full protocol */

		if (!(ch->flags & XPC_C_RCLOSEREQUEST))
			return;

		if (!(ch->flags & XPC_C_CLOSEREPLY)) {
			ch->flags |= XPC_C_CLOSEREPLY;
			xpc_arch_ops.send_chctl_closereply(ch, irq_flags);
		}

		if (!(ch->flags & XPC_C_RCLOSEREPLY))
			return;
	}

	/* wake those waiting for notify completion */
	if (atomic_read(&ch->n_to_notify) > 0) {
		/* we do callout while holding ch->lock, callout can't block */
		xpc_arch_ops.notify_senders_of_disconnect(ch);
	}

	/* both sides are disconnected now */

	if (ch->flags & XPC_C_DISCONNECTINGCALLOUT_MADE) {
		spin_unlock_irqrestore(&ch->lock, *irq_flags);
		xpc_disconnect_callout(ch, xpDisconnected);
		spin_lock_irqsave(&ch->lock, *irq_flags);
	}

	DBUG_ON(atomic_read(&ch->n_to_notify) != 0);

	/* it's now safe to free the channel's message queues */
	xpc_arch_ops.teardown_msg_structures(ch);

	ch->func = NULL;
	ch->key = NULL;
	ch->entry_size = 0;
	ch->local_nentries = 0;
	ch->remote_nentries = 0;
	ch->kthreads_assigned_limit = 0;
	ch->kthreads_idle_limit = 0;

	/*
	 * Mark the channel disconnected and clear all other flags, including
	 * XPC_C_SETUP (because of call to
	 * xpc_arch_ops.teardown_msg_structures()) but not including
	 * XPC_C_WDISCONNECT (if it was set).
	 */
	ch->flags = (XPC_C_DISCONNECTED | (ch->flags & XPC_C_WDISCONNECT));

	atomic_dec(&part->nchannels_active);

	if (channel_was_connected) {
		dev_info(xpc_chan, "channel %d to partition %d disconnected, "
			 "reason=%d\n", ch->number, ch->partid, ch->reason);
	}

	if (ch->flags & XPC_C_WDISCONNECT) {
		/* we won't lose the CPU since we're holding ch->lock */
		complete(&ch->wdisconnect_wait);
	} else if (ch->delayed_chctl_flags) {
		if (part->act_state != XPC_P_AS_DEACTIVATING) {
			/* time to take action on any delayed chctl flags */
			spin_lock(&part->chctl_lock);
			part->chctl.flags[ch->number] |=
			    ch->delayed_chctl_flags;
			spin_unlock(&part->chctl_lock);
		}
		ch->delayed_chctl_flags = 0;
	}
}
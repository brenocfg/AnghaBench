#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct xpc_partition {int /*<<< orphan*/  nchannels_engaged; struct xpc_channel* channels; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  kthreads_assigned; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int (* n_of_deliverable_payloads ) (struct xpc_channel*) ;int /*<<< orphan*/  (* indicate_partition_disengaged ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int XPC_C_CONNECTEDCALLOUT ; 
 int XPC_C_CONNECTEDCALLOUT_MADE ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_DISCONNECTINGCALLOUT ; 
 int XPC_C_DISCONNECTINGCALLOUT_MADE ; 
 short XPC_UNPACK_ARG1 (void*) ; 
 size_t XPC_UNPACK_ARG2 (void*) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,short,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpDisconnecting ; 
 int /*<<< orphan*/  xpc_activate_kthreads (struct xpc_channel*,int) ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_connected_callout (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_disconnect_callout (struct xpc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_kthread_waitmsgs (struct xpc_partition*,struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static int
xpc_kthread_start(void *args)
{
	short partid = XPC_UNPACK_ARG1(args);
	u16 ch_number = XPC_UNPACK_ARG2(args);
	struct xpc_partition *part = &xpc_partitions[partid];
	struct xpc_channel *ch;
	int n_needed;
	unsigned long irq_flags;
	int (*n_of_deliverable_payloads) (struct xpc_channel *) =
		xpc_arch_ops.n_of_deliverable_payloads;

	dev_dbg(xpc_chan, "kthread starting, partid=%d, channel=%d\n",
		partid, ch_number);

	ch = &part->channels[ch_number];

	if (!(ch->flags & XPC_C_DISCONNECTING)) {

		/* let registerer know that connection has been established */

		spin_lock_irqsave(&ch->lock, irq_flags);
		if (!(ch->flags & XPC_C_CONNECTEDCALLOUT)) {
			ch->flags |= XPC_C_CONNECTEDCALLOUT;
			spin_unlock_irqrestore(&ch->lock, irq_flags);

			xpc_connected_callout(ch);

			spin_lock_irqsave(&ch->lock, irq_flags);
			ch->flags |= XPC_C_CONNECTEDCALLOUT_MADE;
			spin_unlock_irqrestore(&ch->lock, irq_flags);

			/*
			 * It is possible that while the callout was being
			 * made that the remote partition sent some messages.
			 * If that is the case, we may need to activate
			 * additional kthreads to help deliver them. We only
			 * need one less than total #of messages to deliver.
			 */
			n_needed = n_of_deliverable_payloads(ch) - 1;
			if (n_needed > 0 && !(ch->flags & XPC_C_DISCONNECTING))
				xpc_activate_kthreads(ch, n_needed);

		} else {
			spin_unlock_irqrestore(&ch->lock, irq_flags);
		}

		xpc_kthread_waitmsgs(part, ch);
	}

	/* let registerer know that connection is disconnecting */

	spin_lock_irqsave(&ch->lock, irq_flags);
	if ((ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) &&
	    !(ch->flags & XPC_C_DISCONNECTINGCALLOUT)) {
		ch->flags |= XPC_C_DISCONNECTINGCALLOUT;
		spin_unlock_irqrestore(&ch->lock, irq_flags);

		xpc_disconnect_callout(ch, xpDisconnecting);

		spin_lock_irqsave(&ch->lock, irq_flags);
		ch->flags |= XPC_C_DISCONNECTINGCALLOUT_MADE;
	}
	spin_unlock_irqrestore(&ch->lock, irq_flags);

	if (atomic_dec_return(&ch->kthreads_assigned) == 0 &&
	    atomic_dec_return(&part->nchannels_engaged) == 0) {
		xpc_arch_ops.indicate_partition_disengaged(part);
	}

	xpc_msgqueue_deref(ch);

	dev_dbg(xpc_chan, "kthread exiting, partid=%d, channel=%d\n",
		partid, ch_number);

	xpc_part_deref(part);
	return 0;
}
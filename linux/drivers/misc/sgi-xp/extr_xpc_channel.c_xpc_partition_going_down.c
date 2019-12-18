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
struct xpc_partition {int nchannels; struct xpc_channel* channels; } ;
struct xpc_channel {int /*<<< orphan*/  lock; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_DISCONNECT_CHANNEL (struct xpc_channel*,int,unsigned long*) ; 
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_ref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part_ref (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (struct xpc_partition*) ; 

void
xpc_partition_going_down(struct xpc_partition *part, enum xp_retval reason)
{
	unsigned long irq_flags;
	int ch_number;
	struct xpc_channel *ch;

	dev_dbg(xpc_chan, "deactivating partition %d, reason=%d\n",
		XPC_PARTID(part), reason);

	if (!xpc_part_ref(part)) {
		/* infrastructure for this partition isn't currently set up */
		return;
	}

	/* disconnect channels associated with the partition going down */

	for (ch_number = 0; ch_number < part->nchannels; ch_number++) {
		ch = &part->channels[ch_number];

		xpc_msgqueue_ref(ch);
		spin_lock_irqsave(&ch->lock, irq_flags);

		XPC_DISCONNECT_CHANNEL(ch, reason, &irq_flags);

		spin_unlock_irqrestore(&ch->lock, irq_flags);
		xpc_msgqueue_deref(ch);
	}

	xpc_wakeup_channel_mgr(part);

	xpc_part_deref(part);
}
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
struct xpc_channel_sn2 {int /*<<< orphan*/ * remote_msgqueue; int /*<<< orphan*/  remote_msgqueue_base; } ;
struct TYPE_2__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int remote_nentries; int entry_size; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  lock; TYPE_1__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int xpNoMemory ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/ * xpc_kzalloc_cacheline_aligned (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum xp_retval
xpc_allocate_remote_msgqueue_sn2(struct xpc_channel *ch)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	unsigned long irq_flags;
	int nentries;
	size_t nbytes;

	DBUG_ON(ch->remote_nentries <= 0);

	for (nentries = ch->remote_nentries; nentries > 0; nentries--) {

		nbytes = nentries * ch->entry_size;
		ch_sn2->remote_msgqueue =
		    xpc_kzalloc_cacheline_aligned(nbytes, GFP_KERNEL, &ch_sn2->
						  remote_msgqueue_base);
		if (ch_sn2->remote_msgqueue == NULL)
			continue;

		spin_lock_irqsave(&ch->lock, irq_flags);
		if (nentries < ch->remote_nentries) {
			dev_dbg(xpc_chan, "nentries=%d remote_nentries=%d, "
				"partid=%d, channel=%d\n", nentries,
				ch->remote_nentries, ch->partid, ch->number);

			ch->remote_nentries = nentries;
		}
		spin_unlock_irqrestore(&ch->lock, irq_flags);
		return xpSuccess;
	}

	dev_dbg(xpc_chan, "can't get memory for cached remote message queue, "
		"partid=%d, channel=%d\n", ch->partid, ch->number);
	return xpNoMemory;
}
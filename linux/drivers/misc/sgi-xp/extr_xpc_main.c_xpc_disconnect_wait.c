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
struct TYPE_2__ {int* flags; } ;
struct xpc_partition {scalar_t__ act_state; int /*<<< orphan*/  chctl_lock; TYPE_1__ chctl; struct xpc_channel* channels; } ;
struct xpc_channel {int flags; int delayed_chctl_flags; size_t number; int /*<<< orphan*/  lock; int /*<<< orphan*/  wdisconnect_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_DISCONNECTED ; 
 int XPC_C_WDISCONNECT ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 short xp_max_npartitions ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (struct xpc_partition*) ; 

void
xpc_disconnect_wait(int ch_number)
{
	unsigned long irq_flags;
	short partid;
	struct xpc_partition *part;
	struct xpc_channel *ch;
	int wakeup_channel_mgr;

	/* now wait for all callouts to the caller's function to cease */
	for (partid = 0; partid < xp_max_npartitions; partid++) {
		part = &xpc_partitions[partid];

		if (!xpc_part_ref(part))
			continue;

		ch = &part->channels[ch_number];

		if (!(ch->flags & XPC_C_WDISCONNECT)) {
			xpc_part_deref(part);
			continue;
		}

		wait_for_completion(&ch->wdisconnect_wait);

		spin_lock_irqsave(&ch->lock, irq_flags);
		DBUG_ON(!(ch->flags & XPC_C_DISCONNECTED));
		wakeup_channel_mgr = 0;

		if (ch->delayed_chctl_flags) {
			if (part->act_state != XPC_P_AS_DEACTIVATING) {
				spin_lock(&part->chctl_lock);
				part->chctl.flags[ch->number] |=
				    ch->delayed_chctl_flags;
				spin_unlock(&part->chctl_lock);
				wakeup_channel_mgr = 1;
			}
			ch->delayed_chctl_flags = 0;
		}

		ch->flags &= ~XPC_C_WDISCONNECT;
		spin_unlock_irqrestore(&ch->lock, irq_flags);

		if (wakeup_channel_mgr)
			xpc_wakeup_channel_mgr(part);

		xpc_part_deref(part);
	}
}
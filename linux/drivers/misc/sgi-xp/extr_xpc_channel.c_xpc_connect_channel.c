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
struct xpc_registration {scalar_t__ entry_size; int /*<<< orphan*/  mutex; int /*<<< orphan*/  nentries; int /*<<< orphan*/  key; int /*<<< orphan*/ * func; int /*<<< orphan*/  idle_limit; int /*<<< orphan*/  assigned_limit; } ;
struct xpc_channel {size_t number; int flags; int reason; scalar_t__ entry_size; size_t partid; int /*<<< orphan*/  lock; int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  key; int /*<<< orphan*/ * func; int /*<<< orphan*/  kthreads_active; int /*<<< orphan*/  kthreads_idle; int /*<<< orphan*/  kthreads_assigned; int /*<<< orphan*/  kthreads_idle_limit; int /*<<< orphan*/  kthreads_assigned_limit; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_chctl_openrequest ) (struct xpc_channel*,unsigned long*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  nchannels_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  XPC_CHANNEL_REGISTERED (size_t) ; 
 int XPC_C_CONNECTED ; 
 int XPC_C_CONNECTING ; 
 int XPC_C_DISCONNECTED ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_OPENREQUEST ; 
 int XPC_C_ROPENREQUEST ; 
 int /*<<< orphan*/  XPC_DISCONNECT_CHANNEL (struct xpc_channel*,int,unsigned long*) ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xpc_channel*,unsigned long*) ; 
 int xpRetry ; 
 int xpSuccess ; 
 int xpUnequalMsgSizes ; 
 int xpUnregistered ; 
 TYPE_2__ xpc_arch_ops ; 
 TYPE_1__* xpc_partitions ; 
 int /*<<< orphan*/  xpc_process_connect (struct xpc_channel*,unsigned long*) ; 
 struct xpc_registration* xpc_registrations ; 

__attribute__((used)) static enum xp_retval
xpc_connect_channel(struct xpc_channel *ch)
{
	unsigned long irq_flags;
	struct xpc_registration *registration = &xpc_registrations[ch->number];

	if (mutex_trylock(&registration->mutex) == 0)
		return xpRetry;

	if (!XPC_CHANNEL_REGISTERED(ch->number)) {
		mutex_unlock(&registration->mutex);
		return xpUnregistered;
	}

	spin_lock_irqsave(&ch->lock, irq_flags);

	DBUG_ON(ch->flags & XPC_C_CONNECTED);
	DBUG_ON(ch->flags & XPC_C_OPENREQUEST);

	if (ch->flags & XPC_C_DISCONNECTING) {
		spin_unlock_irqrestore(&ch->lock, irq_flags);
		mutex_unlock(&registration->mutex);
		return ch->reason;
	}

	/* add info from the channel connect registration to the channel */

	ch->kthreads_assigned_limit = registration->assigned_limit;
	ch->kthreads_idle_limit = registration->idle_limit;
	DBUG_ON(atomic_read(&ch->kthreads_assigned) != 0);
	DBUG_ON(atomic_read(&ch->kthreads_idle) != 0);
	DBUG_ON(atomic_read(&ch->kthreads_active) != 0);

	ch->func = registration->func;
	DBUG_ON(registration->func == NULL);
	ch->key = registration->key;

	ch->local_nentries = registration->nentries;

	if (ch->flags & XPC_C_ROPENREQUEST) {
		if (registration->entry_size != ch->entry_size) {
			/* the local and remote sides aren't the same */

			/*
			 * Because XPC_DISCONNECT_CHANNEL() can block we're
			 * forced to up the registration sema before we unlock
			 * the channel lock. But that's okay here because we're
			 * done with the part that required the registration
			 * sema. XPC_DISCONNECT_CHANNEL() requires that the
			 * channel lock be locked and will unlock and relock
			 * the channel lock as needed.
			 */
			mutex_unlock(&registration->mutex);
			XPC_DISCONNECT_CHANNEL(ch, xpUnequalMsgSizes,
					       &irq_flags);
			spin_unlock_irqrestore(&ch->lock, irq_flags);
			return xpUnequalMsgSizes;
		}
	} else {
		ch->entry_size = registration->entry_size;

		XPC_SET_REASON(ch, 0, 0);
		ch->flags &= ~XPC_C_DISCONNECTED;

		atomic_inc(&xpc_partitions[ch->partid].nchannels_active);
	}

	mutex_unlock(&registration->mutex);

	/* initiate the connection */

	ch->flags |= (XPC_C_OPENREQUEST | XPC_C_CONNECTING);
	xpc_arch_ops.send_chctl_openrequest(ch, &irq_flags);

	xpc_process_connect(ch, &irq_flags);

	spin_unlock_irqrestore(&ch->lock, irq_flags);

	return xpSuccess;
}
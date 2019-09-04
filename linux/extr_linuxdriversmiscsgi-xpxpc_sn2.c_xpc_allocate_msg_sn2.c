#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct xpc_msg_sn2 {scalar_t__ flags; int number; } ;
struct TYPE_6__ {int put; } ;
struct TYPE_5__ {int get; } ;
struct xpc_channel_sn2 {scalar_t__ local_msgqueue; TYPE_3__ w_local_GP; TYPE_2__ w_remote_GP; } ;
struct TYPE_4__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int local_nentries; int entry_size; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; TYPE_1__ sn; } ;
typedef  int s64 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_NOWAIT ; 
 int cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int xpInterrupted ; 
 int xpNoWait ; 
 int xpSuccess ; 
 int xpTimeout ; 
 int xpc_allocate_msg_wait (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_send_chctl_local_msgrequest_sn2 (struct xpc_channel*) ; 

__attribute__((used)) static enum xp_retval
xpc_allocate_msg_sn2(struct xpc_channel *ch, u32 flags,
		     struct xpc_msg_sn2 **address_of_msg)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	struct xpc_msg_sn2 *msg;
	enum xp_retval ret;
	s64 put;

	/*
	 * Get the next available message entry from the local message queue.
	 * If none are available, we'll make sure that we grab the latest
	 * GP values.
	 */
	ret = xpTimeout;

	while (1) {

		put = ch_sn2->w_local_GP.put;
		smp_rmb();	/* guarantee that .put loads before .get */
		if (put - ch_sn2->w_remote_GP.get < ch->local_nentries) {

			/* There are available message entries. We need to try
			 * to secure one for ourselves. We'll do this by trying
			 * to increment w_local_GP.put as long as someone else
			 * doesn't beat us to it. If they do, we'll have to
			 * try again.
			 */
			if (cmpxchg(&ch_sn2->w_local_GP.put, put, put + 1) ==
			    put) {
				/* we got the entry referenced by put */
				break;
			}
			continue;	/* try again */
		}

		/*
		 * There aren't any available msg entries at this time.
		 *
		 * In waiting for a message entry to become available,
		 * we set a timeout in case the other side is not sending
		 * completion interrupts. This lets us fake a notify IRQ
		 * that will cause the notify IRQ handler to fetch the latest
		 * GP values as if an interrupt was sent by the other side.
		 */
		if (ret == xpTimeout)
			xpc_send_chctl_local_msgrequest_sn2(ch);

		if (flags & XPC_NOWAIT)
			return xpNoWait;

		ret = xpc_allocate_msg_wait(ch);
		if (ret != xpInterrupted && ret != xpTimeout)
			return ret;
	}

	/* get the message's address and initialize it */
	msg = (struct xpc_msg_sn2 *)((u64)ch_sn2->local_msgqueue +
				     (put % ch->local_nentries) *
				     ch->entry_size);

	DBUG_ON(msg->flags != 0);
	msg->number = put;

	dev_dbg(xpc_chan, "w_local_GP.put changed to %lld; msg=0x%p, "
		"msg_number=%lld, partid=%d, channel=%d\n", put + 1,
		(void *)msg, msg->number, ch->partid, ch->number);

	*address_of_msg = msg;
	return xpSuccess;
}
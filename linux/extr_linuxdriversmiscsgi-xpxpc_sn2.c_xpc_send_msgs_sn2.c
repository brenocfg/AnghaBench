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
struct xpc_msg_sn2 {int flags; } ;
struct TYPE_5__ {int put; } ;
struct xpc_channel_sn2 {TYPE_3__* local_GP; scalar_t__ local_msgqueue; TYPE_2__ w_local_GP; } ;
struct TYPE_4__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int local_nentries; int entry_size; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; TYPE_1__ sn; } ;
typedef  int s64 ;
struct TYPE_6__ {int put; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_M_SN2_READY ; 
 int cmpxchg_rel (int*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_send_chctl_msgrequest_sn2 (struct xpc_channel*) ; 

__attribute__((used)) static void
xpc_send_msgs_sn2(struct xpc_channel *ch, s64 initial_put)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	struct xpc_msg_sn2 *msg;
	s64 put = initial_put + 1;
	int send_msgrequest = 0;

	while (1) {

		while (1) {
			if (put == ch_sn2->w_local_GP.put)
				break;

			msg = (struct xpc_msg_sn2 *)((u64)ch_sn2->
						     local_msgqueue + (put %
						     ch->local_nentries) *
						     ch->entry_size);

			if (!(msg->flags & XPC_M_SN2_READY))
				break;

			put++;
		}

		if (put == initial_put) {
			/* nothing's changed */
			break;
		}

		if (cmpxchg_rel(&ch_sn2->local_GP->put, initial_put, put) !=
		    initial_put) {
			/* someone else beat us to it */
			DBUG_ON(ch_sn2->local_GP->put < initial_put);
			break;
		}

		/* we just set the new value of local_GP->put */

		dev_dbg(xpc_chan, "local_GP->put changed to %lld, partid=%d, "
			"channel=%d\n", put, ch->partid, ch->number);

		send_msgrequest = 1;

		/*
		 * We need to ensure that the message referenced by
		 * local_GP->put is not XPC_M_SN2_READY or that local_GP->put
		 * equals w_local_GP.put, so we'll go have a look.
		 */
		initial_put = put;
	}

	if (send_msgrequest)
		xpc_send_chctl_msgrequest_sn2(ch);
}
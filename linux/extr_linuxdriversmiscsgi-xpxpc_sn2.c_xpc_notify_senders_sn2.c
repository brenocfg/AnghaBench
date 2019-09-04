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
typedef  scalar_t__ u8 ;
struct xpc_notify_sn2 {scalar_t__ type; int /*<<< orphan*/  key; int /*<<< orphan*/  (* func ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ get; } ;
struct TYPE_5__ {struct xpc_notify_sn2* notify_queue; TYPE_1__ w_remote_GP; } ;
struct TYPE_6__ {TYPE_2__ sn2; } ;
struct xpc_channel {scalar_t__ local_nentries; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  n_to_notify; TYPE_3__ sn; } ;
typedef  scalar_t__ s64 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 scalar_t__ XPC_N_CALL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cmpxchg (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_chan ; 

__attribute__((used)) static void
xpc_notify_senders_sn2(struct xpc_channel *ch, enum xp_retval reason, s64 put)
{
	struct xpc_notify_sn2 *notify;
	u8 notify_type;
	s64 get = ch->sn.sn2.w_remote_GP.get - 1;

	while (++get < put && atomic_read(&ch->n_to_notify) > 0) {

		notify = &ch->sn.sn2.notify_queue[get % ch->local_nentries];

		/*
		 * See if the notify entry indicates it was associated with
		 * a message who's sender wants to be notified. It is possible
		 * that it is, but someone else is doing or has done the
		 * notification.
		 */
		notify_type = notify->type;
		if (notify_type == 0 ||
		    cmpxchg(&notify->type, notify_type, 0) != notify_type) {
			continue;
		}

		DBUG_ON(notify_type != XPC_N_CALL);

		atomic_dec(&ch->n_to_notify);

		if (notify->func != NULL) {
			dev_dbg(xpc_chan, "notify->func() called, notify=0x%p "
				"msg_number=%lld partid=%d channel=%d\n",
				(void *)notify, get, ch->partid, ch->number);

			notify->func(reason, ch->partid, ch->number,
				     notify->key);

			dev_dbg(xpc_chan, "notify->func() returned, notify=0x%p"
				" msg_number=%lld partid=%d channel=%d\n",
				(void *)notify, get, ch->partid, ch->number);
		}
	}
}
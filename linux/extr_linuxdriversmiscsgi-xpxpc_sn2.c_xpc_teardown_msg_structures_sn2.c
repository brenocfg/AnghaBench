#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ put; scalar_t__ get; } ;
struct TYPE_9__ {scalar_t__ put; scalar_t__ get; } ;
struct TYPE_8__ {scalar_t__ put; scalar_t__ get; } ;
struct xpc_channel_sn2 {int /*<<< orphan*/ * notify_queue; int /*<<< orphan*/ * remote_msgqueue; int /*<<< orphan*/ * remote_msgqueue_base; int /*<<< orphan*/ * local_msgqueue; int /*<<< orphan*/ * local_msgqueue_base; scalar_t__ next_msg_to_pull; TYPE_5__ w_remote_GP; TYPE_4__ w_local_GP; TYPE_3__ remote_GP; TYPE_2__* local_GP; scalar_t__ remote_msgqueue_pa; } ;
struct TYPE_6__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  lock; TYPE_1__ sn; } ;
struct TYPE_7__ {scalar_t__ put; scalar_t__ get; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_SETUP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpc_chan ; 

__attribute__((used)) static void
xpc_teardown_msg_structures_sn2(struct xpc_channel *ch)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;

	DBUG_ON(!spin_is_locked(&ch->lock));

	ch_sn2->remote_msgqueue_pa = 0;

	ch_sn2->local_GP->get = 0;
	ch_sn2->local_GP->put = 0;
	ch_sn2->remote_GP.get = 0;
	ch_sn2->remote_GP.put = 0;
	ch_sn2->w_local_GP.get = 0;
	ch_sn2->w_local_GP.put = 0;
	ch_sn2->w_remote_GP.get = 0;
	ch_sn2->w_remote_GP.put = 0;
	ch_sn2->next_msg_to_pull = 0;

	if (ch->flags & XPC_C_SETUP) {
		dev_dbg(xpc_chan, "ch->flags=0x%x, partid=%d, channel=%d\n",
			ch->flags, ch->partid, ch->number);

		kfree(ch_sn2->local_msgqueue_base);
		ch_sn2->local_msgqueue = NULL;
		kfree(ch_sn2->remote_msgqueue_base);
		ch_sn2->remote_msgqueue = NULL;
		kfree(ch_sn2->notify_queue);
		ch_sn2->notify_queue = NULL;
	}
}
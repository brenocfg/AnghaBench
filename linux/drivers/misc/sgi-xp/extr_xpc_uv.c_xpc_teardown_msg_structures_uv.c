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
struct xpc_channel_uv {int /*<<< orphan*/ * recv_msg_slots; int /*<<< orphan*/  recv_msg_list; int /*<<< orphan*/ * send_msg_slots; int /*<<< orphan*/  msg_slot_free_list; int /*<<< orphan*/ * cached_notify_gru_mq_desc; } ;
struct TYPE_2__ {struct xpc_channel_uv uv; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  lock; TYPE_1__ sn; } ;

/* Variables and functions */
 int XPC_C_SETUP ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpc_init_fifo_uv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xpc_teardown_msg_structures_uv(struct xpc_channel *ch)
{
	struct xpc_channel_uv *ch_uv = &ch->sn.uv;

	lockdep_assert_held(&ch->lock);

	kfree(ch_uv->cached_notify_gru_mq_desc);
	ch_uv->cached_notify_gru_mq_desc = NULL;

	if (ch->flags & XPC_C_SETUP) {
		xpc_init_fifo_uv(&ch_uv->msg_slot_free_list);
		kfree(ch_uv->send_msg_slots);
		xpc_init_fifo_uv(&ch_uv->recv_msg_list);
		kfree(ch_uv->recv_msg_slots);
	}
}
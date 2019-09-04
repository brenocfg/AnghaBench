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
struct xpc_msg_sn2 {int flags; scalar_t__ number; } ;
struct TYPE_6__ {scalar_t__ put; } ;
struct TYPE_5__ {int /*<<< orphan*/  put; } ;
struct xpc_channel_sn2 {scalar_t__ remote_msgqueue; TYPE_3__ remote_GP; TYPE_2__ w_remote_GP; } ;
struct TYPE_4__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {scalar_t__ remote_nentries; scalar_t__ entry_size; TYPE_1__ sn; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_M_SN2_DONE ; 
 int XPC_M_SN2_READY ; 
 scalar_t__ max (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
xpc_clear_remote_msgqueue_flags_sn2(struct xpc_channel *ch)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	struct xpc_msg_sn2 *msg;
	s64 put, remote_nentries = ch->remote_nentries;

	/* flags are zeroed when the buffer is allocated */
	if (ch_sn2->remote_GP.put < remote_nentries)
		return;

	put = max(ch_sn2->w_remote_GP.put, remote_nentries);
	do {
		msg = (struct xpc_msg_sn2 *)((u64)ch_sn2->remote_msgqueue +
					     (put % remote_nentries) *
					     ch->entry_size);
		DBUG_ON(!(msg->flags & XPC_M_SN2_READY));
		DBUG_ON(!(msg->flags & XPC_M_SN2_DONE));
		DBUG_ON(msg->number != put - remote_nentries);
		msg->flags = 0;
	} while (++put < ch_sn2->remote_GP.put);
}
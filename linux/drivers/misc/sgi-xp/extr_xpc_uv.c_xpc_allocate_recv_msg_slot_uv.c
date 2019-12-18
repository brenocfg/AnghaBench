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
struct TYPE_4__ {int msg_slot_number; } ;
struct xpc_notify_mq_msg_uv {TYPE_2__ hdr; } ;
struct xpc_channel_uv {struct xpc_notify_mq_msg_uv* recv_msg_slots; } ;
struct TYPE_3__ {struct xpc_channel_uv uv; } ;
struct xpc_channel {int remote_nentries; int entry_size; int /*<<< orphan*/  lock; TYPE_1__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xpc_notify_mq_msg_uv* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int xpNoMemory ; 
 int xpSuccess ; 

__attribute__((used)) static enum xp_retval
xpc_allocate_recv_msg_slot_uv(struct xpc_channel *ch)
{
	struct xpc_channel_uv *ch_uv = &ch->sn.uv;
	struct xpc_notify_mq_msg_uv *msg_slot;
	unsigned long irq_flags;
	int nentries;
	int entry;
	size_t nbytes;

	for (nentries = ch->remote_nentries; nentries > 0; nentries--) {
		nbytes = nentries * ch->entry_size;
		ch_uv->recv_msg_slots = kzalloc(nbytes, GFP_KERNEL);
		if (ch_uv->recv_msg_slots == NULL)
			continue;

		for (entry = 0; entry < nentries; entry++) {
			msg_slot = ch_uv->recv_msg_slots +
			    entry * ch->entry_size;

			msg_slot->hdr.msg_slot_number = entry;
		}

		spin_lock_irqsave(&ch->lock, irq_flags);
		if (nentries < ch->remote_nentries)
			ch->remote_nentries = nentries;
		spin_unlock_irqrestore(&ch->lock, irq_flags);
		return xpSuccess;
	}

	return xpNoMemory;
}
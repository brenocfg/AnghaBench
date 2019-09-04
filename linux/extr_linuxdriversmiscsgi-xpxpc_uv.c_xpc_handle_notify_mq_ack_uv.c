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
struct xpc_send_msg_slot_uv {int msg_slot_number; int /*<<< orphan*/ * func; } ;
struct TYPE_4__ {int msg_slot_number; } ;
struct xpc_notify_mq_msg_uv {TYPE_1__ hdr; } ;
struct TYPE_6__ {struct xpc_send_msg_slot_uv* send_msg_slots; } ;
struct TYPE_5__ {TYPE_3__ uv; } ;
struct xpc_channel {int local_nentries; TYPE_2__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  xpMsgDelivered ; 
 int /*<<< orphan*/  xpc_free_msg_slot_uv (struct xpc_channel*,struct xpc_send_msg_slot_uv*) ; 
 int /*<<< orphan*/  xpc_notify_sender_uv (struct xpc_channel*,struct xpc_send_msg_slot_uv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_handle_notify_mq_ack_uv(struct xpc_channel *ch,
			    struct xpc_notify_mq_msg_uv *msg)
{
	struct xpc_send_msg_slot_uv *msg_slot;
	int entry = msg->hdr.msg_slot_number % ch->local_nentries;

	msg_slot = &ch->sn.uv.send_msg_slots[entry];

	BUG_ON(msg_slot->msg_slot_number != msg->hdr.msg_slot_number);
	msg_slot->msg_slot_number += ch->local_nentries;

	if (msg_slot->func != NULL)
		xpc_notify_sender_uv(ch, msg_slot, xpMsgDelivered);

	xpc_free_msg_slot_uv(ch, msg_slot);
}
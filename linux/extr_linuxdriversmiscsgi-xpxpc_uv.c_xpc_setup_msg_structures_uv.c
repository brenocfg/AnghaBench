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
struct xpc_channel_uv {int /*<<< orphan*/  msg_slot_free_list; int /*<<< orphan*/  send_msg_slots; int /*<<< orphan*/ * cached_notify_gru_mq_desc; } ;
struct TYPE_2__ {struct xpc_channel_uv uv; } ;
struct xpc_channel {int flags; TYPE_1__ sn; } ;
struct gru_message_queue_desc {int dummy; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XPC_C_SETUP ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int xpNoMemory ; 
 int xpSuccess ; 
 int xpc_allocate_recv_msg_slot_uv (struct xpc_channel*) ; 
 int xpc_allocate_send_msg_slot_uv (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_init_fifo_uv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum xp_retval
xpc_setup_msg_structures_uv(struct xpc_channel *ch)
{
	static enum xp_retval ret;
	struct xpc_channel_uv *ch_uv = &ch->sn.uv;

	DBUG_ON(ch->flags & XPC_C_SETUP);

	ch_uv->cached_notify_gru_mq_desc = kmalloc(sizeof(struct
						   gru_message_queue_desc),
						   GFP_KERNEL);
	if (ch_uv->cached_notify_gru_mq_desc == NULL)
		return xpNoMemory;

	ret = xpc_allocate_send_msg_slot_uv(ch);
	if (ret == xpSuccess) {

		ret = xpc_allocate_recv_msg_slot_uv(ch);
		if (ret != xpSuccess) {
			kfree(ch_uv->send_msg_slots);
			xpc_init_fifo_uv(&ch_uv->msg_slot_free_list);
		}
	}
	return ret;
}
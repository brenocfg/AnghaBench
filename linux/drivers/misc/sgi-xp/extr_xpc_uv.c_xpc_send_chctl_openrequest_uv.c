#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xpc_channel {int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  entry_size; int /*<<< orphan*/  number; } ;
struct xpc_activate_mq_msg_chctl_openrequest_uv {int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  entry_size; int /*<<< orphan*/  ch_number; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREQUEST_UV ; 
 int /*<<< orphan*/  xpc_send_activate_IRQ_ch_uv (struct xpc_channel*,unsigned long*,struct xpc_activate_mq_msg_chctl_openrequest_uv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_send_chctl_openrequest_uv(struct xpc_channel *ch, unsigned long *irq_flags)
{
	struct xpc_activate_mq_msg_chctl_openrequest_uv msg;

	msg.ch_number = ch->number;
	msg.entry_size = ch->entry_size;
	msg.local_nentries = ch->local_nentries;
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREQUEST_UV);
}
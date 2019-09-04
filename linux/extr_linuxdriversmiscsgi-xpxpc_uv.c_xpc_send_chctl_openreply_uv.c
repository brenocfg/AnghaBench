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
struct xpc_channel {int /*<<< orphan*/  remote_nentries; int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  number; } ;
struct xpc_activate_mq_msg_chctl_openreply_uv {int /*<<< orphan*/  notify_gru_mq_desc_gpa; int /*<<< orphan*/  remote_nentries; int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  ch_number; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int /*<<< orphan*/  gru_mq_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREPLY_UV ; 
 int /*<<< orphan*/  uv_gpa (int /*<<< orphan*/ ) ; 
 TYPE_1__* xpc_notify_mq_uv ; 
 int /*<<< orphan*/  xpc_send_activate_IRQ_ch_uv (struct xpc_channel*,unsigned long*,struct xpc_activate_mq_msg_chctl_openreply_uv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_send_chctl_openreply_uv(struct xpc_channel *ch, unsigned long *irq_flags)
{
	struct xpc_activate_mq_msg_chctl_openreply_uv msg;

	msg.ch_number = ch->number;
	msg.local_nentries = ch->local_nentries;
	msg.remote_nentries = ch->remote_nentries;
	msg.notify_gru_mq_desc_gpa = uv_gpa(xpc_notify_mq_uv->gru_mq_desc);
	xpc_send_activate_IRQ_ch_uv(ch, irq_flags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREPLY_UV);
}
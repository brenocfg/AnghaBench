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
struct xpc_openclose_args {int /*<<< orphan*/  local_msgqueue_pa; int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  remote_nentries; } ;
struct TYPE_3__ {int /*<<< orphan*/  local_msgqueue; struct xpc_openclose_args* local_openclose_args; } ;
struct TYPE_4__ {TYPE_1__ sn2; } ;
struct xpc_channel {TYPE_2__ sn; int /*<<< orphan*/  local_nentries; int /*<<< orphan*/  remote_nentries; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_CHCTL_OPENREPLY ; 
 int /*<<< orphan*/  XPC_SEND_NOTIFY_IRQ_SN2 (struct xpc_channel*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  xp_pa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_send_chctl_openreply_sn2(struct xpc_channel *ch, unsigned long *irq_flags)
{
	struct xpc_openclose_args *args = ch->sn.sn2.local_openclose_args;

	args->remote_nentries = ch->remote_nentries;
	args->local_nentries = ch->local_nentries;
	args->local_msgqueue_pa = xp_pa(ch->sn.sn2.local_msgqueue);
	XPC_SEND_NOTIFY_IRQ_SN2(ch, XPC_CHCTL_OPENREPLY, irq_flags);
}
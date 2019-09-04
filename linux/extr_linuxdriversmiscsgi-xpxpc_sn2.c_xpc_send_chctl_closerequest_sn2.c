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
struct xpc_openclose_args {int /*<<< orphan*/  reason; } ;
struct TYPE_3__ {struct xpc_openclose_args* local_openclose_args; } ;
struct TYPE_4__ {TYPE_1__ sn2; } ;
struct xpc_channel {int /*<<< orphan*/  reason; TYPE_2__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_CHCTL_CLOSEREQUEST ; 
 int /*<<< orphan*/  XPC_SEND_NOTIFY_IRQ_SN2 (struct xpc_channel*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void
xpc_send_chctl_closerequest_sn2(struct xpc_channel *ch,
				unsigned long *irq_flags)
{
	struct xpc_openclose_args *args = ch->sn.sn2.local_openclose_args;

	args->reason = ch->reason;
	XPC_SEND_NOTIFY_IRQ_SN2(ch, XPC_CHCTL_CLOSEREQUEST, irq_flags);
}
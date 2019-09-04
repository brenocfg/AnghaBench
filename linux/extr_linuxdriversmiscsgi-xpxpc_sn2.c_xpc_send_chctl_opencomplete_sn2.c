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
struct xpc_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_CHCTL_OPENCOMPLETE ; 
 int /*<<< orphan*/  XPC_SEND_NOTIFY_IRQ_SN2 (struct xpc_channel*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void
xpc_send_chctl_opencomplete_sn2(struct xpc_channel *ch,
				unsigned long *irq_flags)
{
	XPC_SEND_NOTIFY_IRQ_SN2(ch, XPC_CHCTL_OPENCOMPLETE, irq_flags);
}
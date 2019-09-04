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
struct xpc_partition {int dummy; } ;
struct timer_list {scalar_t__ expires; } ;
struct TYPE_3__ {int /*<<< orphan*/  dropped_notify_IRQ_timer; } ;
struct TYPE_4__ {TYPE_1__ sn2; } ;

/* Variables and functions */
 scalar_t__ XPC_DROPPED_NOTIFY_IRQ_WAIT_INTERVAL ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 struct xpc_partition* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct xpc_partition* part ; 
 TYPE_2__ sn ; 
 int /*<<< orphan*/  xpc_check_for_sent_chctl_flags_sn2 (struct xpc_partition*) ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 scalar_t__ xpc_part_ref (struct xpc_partition*) ; 

__attribute__((used)) static void
xpc_check_for_dropped_notify_IRQ_sn2(struct timer_list *t)
{
	struct xpc_partition *part =
		from_timer(part, t, sn.sn2.dropped_notify_IRQ_timer);

	if (xpc_part_ref(part)) {
		xpc_check_for_sent_chctl_flags_sn2(part);

		t->expires = jiffies + XPC_DROPPED_NOTIFY_IRQ_WAIT_INTERVAL;
		add_timer(t);
		xpc_part_deref(part);
	}
}
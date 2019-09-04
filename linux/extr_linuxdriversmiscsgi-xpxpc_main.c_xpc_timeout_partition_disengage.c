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
struct xpc_partition {scalar_t__ disengage_timeout; } ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {int (* partition_engaged ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  XPC_PARTID (struct xpc_partition*) ; 
 int /*<<< orphan*/  disengage_timer ; 
 struct xpc_partition* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct xpc_partition* part ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int time_is_after_jiffies (scalar_t__) ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_partition_disengaged (struct xpc_partition*) ; 

__attribute__((used)) static void
xpc_timeout_partition_disengage(struct timer_list *t)
{
	struct xpc_partition *part = from_timer(part, t, disengage_timer);

	DBUG_ON(time_is_after_jiffies(part->disengage_timeout));

	(void)xpc_partition_disengaged(part);

	DBUG_ON(part->disengage_timeout != 0);
	DBUG_ON(xpc_arch_ops.partition_engaged(XPC_PARTID(part)));
}
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
struct timer_list {int dummy; } ;
struct ixgbe_adapter {int flags; int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 int HZ ; 
 int IXGBE_FLAG_NEED_LINK_UPDATE ; 
 struct ixgbe_adapter* adapter ; 
 struct ixgbe_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_service_event_schedule (struct ixgbe_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void ixgbe_service_timer(struct timer_list *t)
{
	struct ixgbe_adapter *adapter = from_timer(adapter, t, service_timer);
	unsigned long next_event_offset;

	/* poll faster when waiting for link */
	if (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE)
		next_event_offset = HZ / 10;
	else
		next_event_offset = HZ * 2;

	/* Reset the timer */
	mod_timer(&adapter->service_timer, next_event_offset + jiffies);

	ixgbe_service_event_schedule(adapter);
}
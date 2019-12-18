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
struct ixgbevf_adapter {int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 int HZ ; 
 struct ixgbevf_adapter* adapter ; 
 struct ixgbevf_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_service_event_schedule (struct ixgbevf_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void ixgbevf_service_timer(struct timer_list *t)
{
	struct ixgbevf_adapter *adapter = from_timer(adapter, t,
						     service_timer);

	/* Reset the timer */
	mod_timer(&adapter->service_timer, (HZ * 2) + jiffies);

	ixgbevf_service_event_schedule(adapter);
}
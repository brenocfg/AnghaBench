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
struct igbvf_adapter {int /*<<< orphan*/  watchdog_task; } ;

/* Variables and functions */
 struct igbvf_adapter* adapter ; 
 struct igbvf_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_timer ; 

__attribute__((used)) static void igbvf_watchdog(struct timer_list *t)
{
	struct igbvf_adapter *adapter = from_timer(adapter, t, watchdog_timer);

	/* Do the rest outside of interrupt context */
	schedule_work(&adapter->watchdog_task);
}
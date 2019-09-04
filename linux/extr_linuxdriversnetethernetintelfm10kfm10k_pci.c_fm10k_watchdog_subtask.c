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
struct fm10k_intfc {int /*<<< orphan*/  next_stats_update; scalar_t__ host_ready; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_DOWN ; 
 int /*<<< orphan*/  __FM10K_RESETTING ; 
 int /*<<< orphan*/  fm10k_update_stats (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_watchdog_flush_tx (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_watchdog_host_is_ready (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_watchdog_host_not_ready (struct fm10k_intfc*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_before_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_watchdog_subtask(struct fm10k_intfc *interface)
{
	/* if interface is down do nothing */
	if (test_bit(__FM10K_DOWN, interface->state) ||
	    test_bit(__FM10K_RESETTING, interface->state))
		return;

	if (interface->host_ready)
		fm10k_watchdog_host_is_ready(interface);
	else
		fm10k_watchdog_host_not_ready(interface);

	/* update stats only once every second */
	if (time_is_before_jiffies(interface->next_stats_update))
		fm10k_update_stats(interface);

	/* flush any uncompleted work */
	fm10k_watchdog_flush_tx(interface);
}
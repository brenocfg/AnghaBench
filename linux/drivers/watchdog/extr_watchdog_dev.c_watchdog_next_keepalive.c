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
struct watchdog_device {int timeout; int /*<<< orphan*/  max_hw_heartbeat_ms; struct watchdog_core_data* wd_data; } ;
struct watchdog_core_data {int /*<<< orphan*/  open_deadline; int /*<<< orphan*/  last_keepalive; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min_not_zero (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (unsigned int) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 

__attribute__((used)) static ktime_t watchdog_next_keepalive(struct watchdog_device *wdd)
{
	struct watchdog_core_data *wd_data = wdd->wd_data;
	unsigned int timeout_ms = wdd->timeout * 1000;
	ktime_t keepalive_interval;
	ktime_t last_heartbeat, latest_heartbeat;
	ktime_t virt_timeout;
	unsigned int hw_heartbeat_ms;

	if (watchdog_active(wdd))
		virt_timeout = ktime_add(wd_data->last_keepalive,
					 ms_to_ktime(timeout_ms));
	else
		virt_timeout = wd_data->open_deadline;

	hw_heartbeat_ms = min_not_zero(timeout_ms, wdd->max_hw_heartbeat_ms);
	keepalive_interval = ms_to_ktime(hw_heartbeat_ms / 2);

	/*
	 * To ensure that the watchdog times out wdd->timeout seconds
	 * after the most recent ping from userspace, the last
	 * worker ping has to come in hw_heartbeat_ms before this timeout.
	 */
	last_heartbeat = ktime_sub(virt_timeout, ms_to_ktime(hw_heartbeat_ms));
	latest_heartbeat = ktime_sub(last_heartbeat, ktime_get());
	if (ktime_before(latest_heartbeat, keepalive_interval))
		return latest_heartbeat;
	return keepalive_interval;
}
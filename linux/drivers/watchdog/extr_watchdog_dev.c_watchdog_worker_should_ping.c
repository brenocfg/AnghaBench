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
struct watchdog_device {int dummy; } ;
struct watchdog_core_data {struct watchdog_device* wdd; } ;

/* Variables and functions */
 scalar_t__ watchdog_active (struct watchdog_device*) ; 
 scalar_t__ watchdog_hw_running (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_past_open_deadline (struct watchdog_core_data*) ; 

__attribute__((used)) static bool watchdog_worker_should_ping(struct watchdog_core_data *wd_data)
{
	struct watchdog_device *wdd = wd_data->wdd;

	if (!wdd)
		return false;

	if (watchdog_active(wdd))
		return true;

	return watchdog_hw_running(wdd) && !watchdog_past_open_deadline(wd_data);
}
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
struct watchdog_device {int timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int HV_EINVAL ; 
 int sun4v_mach_set_watchdog (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4v_wdt_ping(struct watchdog_device *wdd)
{
	int hverr;

	/*
	 * HV watchdog timer will round up the timeout
	 * passed in to the nearest multiple of the
	 * watchdog resolution in milliseconds.
	 */
	hverr = sun4v_mach_set_watchdog(wdd->timeout * 1000, NULL);
	if (hverr == HV_EINVAL)
		return -EINVAL;

	return 0;
}
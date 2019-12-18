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
struct watchdog_device {unsigned int timeout; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int pcf2127_wdt_active_ping (struct watchdog_device*) ; 

__attribute__((used)) static int pcf2127_wdt_set_timeout(struct watchdog_device *wdd,
				   unsigned int new_timeout)
{
	dev_dbg(wdd->parent, "new watchdog timeout: %is (old: %is)\n",
		new_timeout, wdd->timeout);

	wdd->timeout = new_timeout;

	return pcf2127_wdt_active_ping(wdd);
}
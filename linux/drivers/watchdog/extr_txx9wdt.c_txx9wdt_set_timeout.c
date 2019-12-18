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
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  txx9wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  txx9wdt_stop (struct watchdog_device*) ; 

__attribute__((used)) static int txx9wdt_set_timeout(struct watchdog_device *wdt_dev,
			       unsigned int new_timeout)
{
	wdt_dev->timeout = new_timeout;
	txx9wdt_stop(wdt_dev);
	txx9wdt_start(wdt_dev);
	return 0;
}
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
 int /*<<< orphan*/  rza_wdt_start (struct watchdog_device*) ; 

__attribute__((used)) static int rza_set_timeout(struct watchdog_device *wdev, unsigned int timeout)
{
	wdev->timeout = timeout;
	rza_wdt_start(wdev);
	return 0;
}
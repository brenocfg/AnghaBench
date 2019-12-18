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
struct omap_wdt_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_wdt_disable (struct omap_wdt_dev*) ; 
 int /*<<< orphan*/  omap_wdt_enable (struct omap_wdt_dev*) ; 
 int /*<<< orphan*/  omap_wdt_reload (struct omap_wdt_dev*) ; 
 int /*<<< orphan*/  omap_wdt_set_timer (struct omap_wdt_dev*,unsigned int) ; 
 struct omap_wdt_dev* to_omap_wdt_dev (struct watchdog_device*) ; 

__attribute__((used)) static int omap_wdt_set_timeout(struct watchdog_device *wdog,
				unsigned int timeout)
{
	struct omap_wdt_dev *wdev = to_omap_wdt_dev(wdog);

	mutex_lock(&wdev->lock);
	omap_wdt_disable(wdev);
	omap_wdt_set_timer(wdev, timeout);
	omap_wdt_enable(wdev);
	omap_wdt_reload(wdev);
	wdog->timeout = timeout;
	mutex_unlock(&wdev->lock);

	return 0;
}
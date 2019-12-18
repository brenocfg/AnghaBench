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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct da9063 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t da9063_wdt_timeout_to_sel (unsigned int) ; 
 int da9063_wdt_update_timeout (struct da9063*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 
 struct da9063* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/ * wdt_timeout ; 

__attribute__((used)) static int da9063_wdt_set_timeout(struct watchdog_device *wdd,
				  unsigned int timeout)
{
	struct da9063 *da9063 = watchdog_get_drvdata(wdd);
	int ret = 0;

	/*
	 * There are two cases when a set_timeout() will be called:
	 * 1. The watchdog is off and someone wants to set the timeout for the
	 *    further use.
	 * 2. The watchdog is already running and a new timeout value should be
	 *    set.
	 *
	 * The watchdog can't store a timeout value not equal zero without
	 * enabling the watchdog, so the timeout must be buffered by the driver.
	 */
	if (watchdog_active(wdd))
		ret = da9063_wdt_update_timeout(da9063, timeout);

	if (ret)
		dev_err(da9063->dev, "Failed to set watchdog timeout (err = %d)\n",
			ret);
	else
		wdd->timeout = wdt_timeout[da9063_wdt_timeout_to_sel(timeout)];

	return ret;
}
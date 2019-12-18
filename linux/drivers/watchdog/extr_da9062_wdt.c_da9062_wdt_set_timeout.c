#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct da9062_watchdog {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int da9062_wdt_timeout_to_sel (unsigned int) ; 
 int da9062_wdt_update_timeout_register (struct da9062_watchdog*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9062_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/ * wdt_timeout ; 

__attribute__((used)) static int da9062_wdt_set_timeout(struct watchdog_device *wdd,
				  unsigned int timeout)
{
	struct da9062_watchdog *wdt = watchdog_get_drvdata(wdd);
	unsigned int selector;
	int ret;

	selector = da9062_wdt_timeout_to_sel(timeout);
	ret = da9062_wdt_update_timeout_register(wdt, selector);
	if (ret)
		dev_err(wdt->hw->dev, "Failed to set watchdog timeout (err = %d)\n",
			ret);
	else
		wdd->timeout = wdt_timeout[selector];

	return ret;
}
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
struct watchdog_device {int dummy; } ;
struct da9062_watchdog {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int da9062_reset_watchdog_timer (struct da9062_watchdog*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9062_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int da9062_wdt_ping(struct watchdog_device *wdd)
{
	struct da9062_watchdog *wdt = watchdog_get_drvdata(wdd);
	int ret;

	ret = da9062_reset_watchdog_timer(wdt);
	if (ret)
		dev_err(wdt->hw->dev, "Failed to ping the watchdog (err = %d)\n",
			ret);

	return ret;
}
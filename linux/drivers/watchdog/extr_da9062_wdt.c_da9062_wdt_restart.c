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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9062AA_CONTROL_F ; 
 int /*<<< orphan*/  DA9062AA_SHUTDOWN_MASK ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9062_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int da9062_wdt_restart(struct watchdog_device *wdd, unsigned long action,
			      void *data)
{
	struct da9062_watchdog *wdt = watchdog_get_drvdata(wdd);
	int ret;

	ret = regmap_write(wdt->hw->regmap,
			   DA9062AA_CONTROL_F,
			   DA9062AA_SHUTDOWN_MASK);
	if (ret)
		dev_alert(wdt->hw->dev, "Failed to shutdown (err = %d)\n",
			  ret);

	/* wait for reset to assert... */
	mdelay(500);

	return ret;
}
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
struct armada_37xx_watchdog {int /*<<< orphan*/  cpu_misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR_ID_RETRIGGER ; 
 int /*<<< orphan*/  CNTR_ID_WDOG ; 
 int /*<<< orphan*/  WDT_TIMER_SELECT ; 
 int /*<<< orphan*/  counter_disable (struct armada_37xx_watchdog*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct armada_37xx_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int armada_37xx_wdt_stop(struct watchdog_device *wdt)
{
	struct armada_37xx_watchdog *dev = watchdog_get_drvdata(wdt);

	counter_disable(dev, CNTR_ID_WDOG);
	counter_disable(dev, CNTR_ID_RETRIGGER);
	regmap_write(dev->cpu_misc, WDT_TIMER_SELECT, 0);

	return 0;
}
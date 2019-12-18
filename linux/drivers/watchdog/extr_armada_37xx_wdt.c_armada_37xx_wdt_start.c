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
struct armada_37xx_watchdog {int /*<<< orphan*/  timeout; int /*<<< orphan*/  cpu_misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR_CTRL_MODE_HWSIG ; 
 int /*<<< orphan*/  CNTR_CTRL_MODE_ONESHOT ; 
 int /*<<< orphan*/  CNTR_CTRL_TRIG_SRC_PREV_CNTR ; 
 int /*<<< orphan*/  CNTR_ID_RETRIGGER ; 
 int /*<<< orphan*/  CNTR_ID_WDOG ; 
 int /*<<< orphan*/  WDT_TIMER_SELECT ; 
 int /*<<< orphan*/  WDT_TIMER_SELECT_VAL ; 
 int /*<<< orphan*/  counter_enable (struct armada_37xx_watchdog*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_counter (struct armada_37xx_watchdog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_counter_value (struct armada_37xx_watchdog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct armada_37xx_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int armada_37xx_wdt_start(struct watchdog_device *wdt)
{
	struct armada_37xx_watchdog *dev = watchdog_get_drvdata(wdt);

	/* select counter 1 as watchdog counter */
	regmap_write(dev->cpu_misc, WDT_TIMER_SELECT, WDT_TIMER_SELECT_VAL);

	/* init counter 0 as retrigger counter for counter 1 */
	init_counter(dev, CNTR_ID_RETRIGGER, CNTR_CTRL_MODE_ONESHOT, 0);
	set_counter_value(dev, CNTR_ID_RETRIGGER, 0);

	/* init counter 1 to be retriggerable by counter 0 end count */
	init_counter(dev, CNTR_ID_WDOG, CNTR_CTRL_MODE_HWSIG,
		     CNTR_CTRL_TRIG_SRC_PREV_CNTR);
	set_counter_value(dev, CNTR_ID_WDOG, dev->timeout);

	/* enable counter 1 */
	counter_enable(dev, CNTR_ID_WDOG);

	/* start counter 1 by forcing immediate end count on counter 0 */
	counter_enable(dev, CNTR_ID_RETRIGGER);

	return 0;
}
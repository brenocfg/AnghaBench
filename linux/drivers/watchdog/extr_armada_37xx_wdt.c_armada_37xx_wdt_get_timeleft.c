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
typedef  unsigned int u64 ;
struct watchdog_device {int dummy; } ;
struct armada_37xx_watchdog {int /*<<< orphan*/  clk_rate; } ;

/* Variables and functions */
 unsigned int CNTR_CTRL_PRESCALE_MIN ; 
 int /*<<< orphan*/  CNTR_ID_WDOG ; 
 int /*<<< orphan*/  do_div (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int get_counter_value (struct armada_37xx_watchdog*,int /*<<< orphan*/ ) ; 
 struct armada_37xx_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int armada_37xx_wdt_get_timeleft(struct watchdog_device *wdt)
{
	struct armada_37xx_watchdog *dev = watchdog_get_drvdata(wdt);
	u64 res;

	res = get_counter_value(dev, CNTR_ID_WDOG) * CNTR_CTRL_PRESCALE_MIN;
	do_div(res, dev->clk_rate);

	return res;
}
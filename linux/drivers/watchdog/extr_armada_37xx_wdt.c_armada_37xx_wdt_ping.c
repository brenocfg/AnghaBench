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
struct armada_37xx_watchdog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR_ID_RETRIGGER ; 
 int /*<<< orphan*/  counter_disable (struct armada_37xx_watchdog*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_enable (struct armada_37xx_watchdog*,int /*<<< orphan*/ ) ; 
 struct armada_37xx_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int armada_37xx_wdt_ping(struct watchdog_device *wdt)
{
	struct armada_37xx_watchdog *dev = watchdog_get_drvdata(wdt);

	/* counter 1 is retriggered by forcing end count on counter 0 */
	counter_disable(dev, CNTR_ID_RETRIGGER);
	counter_enable(dev, CNTR_ID_RETRIGGER);

	return 0;
}